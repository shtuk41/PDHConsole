#pragma once

#include <vector>
#include <string>
#include <pdh.h>

#pragma managed (push, off)

class PerformanceCounter
{
public:
	enum			CounterType {PROCESSOR = 0, PROCESS};
	
	PerformanceCounter(CounterType e, std::string c) : eCounterType(e), counter(c), Query(NULL) {}
	WCHAR*			GetCounterPathBuffer() {return CounterPathBuffer;}
	
	CounterType		GetCounterType() const { return eCounterType;}
	std::string		GetCounter() const {return counter;}

	HQUERY Query;
    HCOUNTER Counter;

protected:
	WCHAR	CounterPathBuffer[PDH_MAX_COUNTER_PATH];

private:

	CounterType eCounterType;
	std::string		counter;
	
};

class	PerformanceCounterProcessor : public PerformanceCounter
{
public:
	PerformanceCounterProcessor(std::string pn, std::string counter);

	std::string 	GetProcessorNumber() const { return processorNumber;}
private:
	std::string		processorNumber;
};

class	PerformanceCounterProcess : public PerformanceCounter
{
public:
	PerformanceCounterProcess(std::string pn, std::string counter);
	std::string		GetProcessName() const { return processName;}
private:
	std::string processName;
};

class PerformanceCounterThread
{
public:
	PerformanceCounterThread(std::string machine, unsigned long interval) : machineName(machine), sampleIntervalMs(interval)  {};
	~PerformanceCounterThread();
	std::string		GetMachineName() const { return machineName;}
	unsigned long	GetSampleIntervalMs() const { return sampleIntervalMs;}
	std::vector<PerformanceCounter *> GetCountersList() const {return counters;}
	void			Add(PerformanceCounter *pcp) { counters.push_back(pcp);}
private:
	std::string		machineName;
	unsigned long	sampleIntervalMs;
	std::vector<PerformanceCounter *>	counters;
};

class LogManager
{
public:

	LogManager();
	std::vector<std::string> GetListOfProcesses(std::string machineName);
	const std::vector<std::string> &GetListOfProcessCounters() const;
	const std::vector<std::string> &GetListOfProcessorCounters() const;
	void BeginLog(std::vector<std::string>);

	static bool IsEndLogFlagSet() { return EndLogFlag;}
	static void SetEndLogFlag() {EndLogFlag = true;}
	static void ResetEndLogFlag() {EndLogFlag = false;}


private:

	static bool EndLogFlag;

	std::vector<std::string> listOfProcessCounters;
	std::vector<std::string> listOfProcessorCounters;

	std::vector<PerformanceCounterThread *> logs;

};

#pragma managed(pop)