#include "stdafx.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <pdhmsg.h>


#include "LogManager.h"

#pragma comment(lib, "pdh.lib")

#pragma managed(push, off)

PerformanceCounterProcessor::PerformanceCounterProcessor(std::string pn, std::string counter) : processorNumber(pn), PerformanceCounter(PerformanceCounter::PROCESSOR, counter) 
{
	//"\\Processor(3)\\% C1 Time");
	std::string path = "\\Processor(" + processorNumber + ")\\" + GetCounter();
	std::wstring  wpath(path.begin(), path.end());
	ZeroMemory(CounterPathBuffer, sizeof(*CounterPathBuffer));
	wcsncpy_s(CounterPathBuffer, PDH_MAX_COUNTER_PATH, wpath.c_str(), wpath.length());

}

PerformanceCounterProcess::PerformanceCounterProcess(std::string pn, std::string counter) : processName(pn), PerformanceCounter(PerformanceCounter::PROCESS, counter) 
{
	std::string path = "\\Process(" + processName + ")\\" + GetCounter();
	std::wstring  wpath(path.begin(), path.end());
	ZeroMemory(CounterPathBuffer, sizeof(*CounterPathBuffer));
	wcsncpy_s(CounterPathBuffer, PDH_MAX_COUNTER_PATH, wpath.c_str(), wpath.length());
}

PerformanceCounterThread::~PerformanceCounterThread()
{
	for (std::vector<PerformanceCounter*>::iterator it = counters.begin(); it != counters.end(); ++it)
	{
		if ((*it)->Query)
		{
			PdhCloseQuery((*it)->Query);
		}

		delete *it;
	}

}

bool LogManager::EndLogFlag = true;

LogManager::LogManager()
{
	listOfProcessorCounters.push_back("% Processor Time");
	listOfProcessorCounters.push_back("% User Time");
	listOfProcessorCounters.push_back("% Privileged Time"); 

	listOfProcessCounters.push_back("Virtual Bytes Peak");
	listOfProcessCounters.push_back("Virtual Bytes");
	listOfProcessCounters.push_back("Page Faults/sec");
	listOfProcessCounters.push_back("Working Set Peak");
	listOfProcessCounters.push_back("Working Set");
	listOfProcessCounters.push_back("Page File Bytes Peak");
	listOfProcessCounters.push_back("Page File Bytes");
	listOfProcessCounters.push_back("Private Bytes");
	listOfProcessCounters.push_back("Thread Count");
	listOfProcessCounters.push_back("Priority Base");
	listOfProcessCounters.push_back("Elapsed Time");
	listOfProcessCounters.push_back("ID Process");
	listOfProcessCounters.push_back("Creating Process ID");
	listOfProcessCounters.push_back("Pool Paged Bytes");
	listOfProcessCounters.push_back("Pool Nonpaged Bytes");
	listOfProcessCounters.push_back("Handle Count");
	listOfProcessCounters.push_back("IO Read Operations/sec");
	listOfProcessCounters.push_back("IO Write Operations/sec");
	listOfProcessCounters.push_back("IO Data Operations/sec");
	listOfProcessCounters.push_back("IO Other Operations/sec");
	listOfProcessCounters.push_back("IO Read Bytes/sec");
	listOfProcessCounters.push_back("IO Write Bytes/sec");
	listOfProcessCounters.push_back("IO Data Bytes/sec");
	listOfProcessCounters.push_back("IO Other Bytes/sec");
	listOfProcessCounters.push_back("Working Set - Private");
}

const std::vector<std::string> &LogManager::GetListOfProcessCounters() const
{
	return listOfProcessCounters;
}

const std::vector<std::string> &LogManager::GetListOfProcessorCounters() const
{
	return listOfProcessorCounters;
}

DWORD WINAPI Thread_PerformanceCounters( LPVOID lpParam ) 
{
	PDH_STATUS Status;
	PDH_FMT_COUNTERVALUE DisplayValue;
    DWORD CounterType;
	SYSTEMTIME SampleTime;
	// Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    PerformanceCounterThread* Data = ((PerformanceCounterThread*)lpParam); 
	std::wofstream outputfile;

	if (Data->GetMachineName().length() != 0)
		outputfile.open(Data->GetMachineName() + ".csv", std::ios::trunc);
	else
		return -1;

	std::vector<PerformanceCounter *> counters = Data->GetCountersList();

	outputfile << "SampleTime,";

	for (std::vector<PerformanceCounter*>::iterator it = counters.begin(); it != counters.end(); ++it)
	{
		Status = PdhOpenQuery(NULL,NULL,&((*it)->Query));

		if (Status != ERROR_SUCCESS)
		{
			outputfile << "PdhOpenQuery failed with status " << Status << std::endl;

			goto Cleanup;
		}

		if (wcslen((*it)->GetCounterPathBuffer()) == 0)
		{
			outputfile << "\nUser did not select any counter." << std::endl;

			goto Cleanup;
		}
		else
		{
			outputfile << (*it)->GetCounterPathBuffer() << ",";
		}

		std::string		mn = Data->GetMachineName();
		std::wstring	machinepath(mn.begin(), mn.end());
		std::wstring	fullpath = L"\\\\" + machinepath + (*it)->GetCounterPathBuffer();

		Status = PdhAddCounter((*it)->Query, fullpath.c_str(), 0, &((*it)->Counter));

		if (Status != ERROR_SUCCESS) 
		{
			outputfile << "PdhAddCounter failed with status " << Status << std::endl;
			goto Cleanup;
		}

		Status = PdhCollectQueryData((*it)->Query);
		if (Status != ERROR_SUCCESS) 
		{
			outputfile <<  "\nPdhCollectQueryData failed with " << Status << std::endl;
			goto Cleanup;
		}
	}

	outputfile << std::endl;

	while (!LogManager::IsEndLogFlagSet())
	{
		GetLocalTime(&SampleTime);
		outputfile << SampleTime.wMonth << "/" << SampleTime.wDay << "/" << SampleTime.wYear << " " << SampleTime.wHour << ":" << SampleTime.wMinute << ":" <<SampleTime.wSecond << "." << SampleTime.wMilliseconds << ",";

		for (std::vector<PerformanceCounter*>::iterator it = counters.begin(); it != counters.end(); ++it)
		{
			Status = PdhCollectQueryData((*it)->Query);
			if (Status != ERROR_SUCCESS) 
			{
				outputfile << "PdhCollectQueryData failed with " << Status << std::endl;
				goto Cleanup;
			}

			Status = PdhGetFormattedCounterValue((*it)->Counter,
												 PDH_FMT_DOUBLE,
												 &CounterType,
												 &DisplayValue);

			if (Status != ERROR_SUCCESS) 
			{
				switch(Status)
				{
					case PDH_INVALID_ARGUMENT:
						outputfile << "\nPdhGetFormattedCounterValue with PDH_INVALID_ARGUMENT" << std::endl;
						break;
					case PDH_INVALID_DATA:
						outputfile << "\nPdhGetFormattedCounterValue with PDH_INVALID_DATA" << std::endl;
						break;
					case PDH_INVALID_HANDLE:
						outputfile << "\nPdhGetFormattedCounterValue with PDH_INVALID_HANDLE" << std::endl;
						break;
				}
				
				goto Cleanup;
			}


			outputfile << DisplayValue.doubleValue << ",";
		}

		outputfile << std::endl;

		Sleep(Data->GetSampleIntervalMs());
	}

Cleanup:

    return 0; 
} 

void LogManager::BeginLog(std::vector<std::string> addedCounters)
{
	if (logs.size() > 0)
	{
		for (std::vector<PerformanceCounterThread*>::iterator it = logs.begin(); it != logs.end(); ++it)
		{
			delete *it;
		}

		logs.clear();
	}

	for (std::vector<std::string>::iterator ac = addedCounters.begin(); ac != addedCounters.end(); ++ac)
	{
		std::string line = *ac;

		std::istringstream ss(line);

		std::string		elem[4];
		
		for (int e = 0; e < 4; e++)
		{
			std::getline(ss, elem[e], ',');
		}

		bool threadFound = false;

		for (std::vector<PerformanceCounterThread *>::iterator pcti = logs.begin(); pcti != logs.end(); ++pcti)
		{
			std::string machineName = (*pcti)->GetMachineName();
			if (machineName.compare(elem[1]) == 0)
			{
				threadFound = true;
				PerformanceCounter *pc;
				if (elem[0].compare("Process") == 0)
				{
					pc = new PerformanceCounterProcess(elem[2], elem[3]);
				}
				else
				{
					pc = new PerformanceCounterProcessor(elem[2], elem[3]);
				}

				(*pcti)->Add(pc);

				break;
			}
		}

		if (!threadFound)
		{
			PerformanceCounterThread *pct = new PerformanceCounterThread(elem[1], 1000);

			PerformanceCounter *pc;
			if (elem[0].compare("Process") == 0)
			{
				pc = new PerformanceCounterProcess(elem[2], elem[3]);
			}
			else
			{
				pc = new PerformanceCounterProcessor(elem[2], elem[3]);
			}

			pct->Add(pc);

			logs.push_back(pct);
		}
	}

	/*PerformanceCounterThread *pct = new PerformanceCounterThread("mymobilpc", 1000);
	PerformanceCounterProcessor *pcp1 = new PerformanceCounterProcessor(0, "% Processor Time");
	
	pct->Add(pcp1);
	pct->Add(pcp2);

	logs.push_back(pct);*/

	for (std::vector<PerformanceCounterThread *>::iterator pcti = logs.begin(); pcti != logs.end(); ++pcti)
	{
		HANDLE Handle_Of_Thread_1 = 0;
	
		Handle_Of_Thread_1 = CreateThread( NULL, 0, Thread_PerformanceCounters, *pcti, 0, NULL);  
		if ( Handle_Of_Thread_1 == NULL)
			ExitProcess(0);
	}

	
}

#pragma managed(pop)

