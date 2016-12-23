#pragma once
#include <msclr\marshal_cppstd.h>
#include <vector>
#include <string>

#include "LogManager.h"


namespace PerformanceCounterLogger {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			logManager = new LogManager();

			PopulateProcessCounters();
			PopulateProcessorCounter();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBoxMachineName;
	protected: 

	private: System::Windows::Forms::Label^  labelMachine;

	protected: 


	private: System::Windows::Forms::Label^  labelProcessorCounters;
	private: System::Windows::Forms::Button^  buttonAddProcessorCounter;
	private: System::Windows::Forms::Button^  buttonAddProcessCounter;
	private: System::Windows::Forms::ListBox^  listBoxProcessCounters;





	private: System::Windows::Forms::ListBox^  listBoxProcessorCounters;

	private: System::Windows::Forms::Label^  labelProcess;
	private: System::Windows::Forms::Label^  labelProcessCounters;



	private: System::Windows::Forms::Label^  labelProcessorID;
	private: System::Windows::Forms::ListBox^  listBoxAddedPerformanceCounters;



	private: System::Windows::Forms::Label^  labelAddedPerformanceCounters;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownProcessorID;



	private: System::Windows::Forms::Button^  buttonStartStop;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::TextBox^  textBoxProcessName;
	private: System::Windows::Forms::Button^  buttonClearAddedPerformanceCounters;
	private: System::Windows::Forms::Button^  buttonSaveAddedPerformanceCounters;
	private: System::Windows::Forms::Button^  buttonLoadAddedPerformanceCounters;

		LogManager	*logManager;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBoxMachineName = (gcnew System::Windows::Forms::TextBox());
			this->labelMachine = (gcnew System::Windows::Forms::Label());
			this->labelProcessorCounters = (gcnew System::Windows::Forms::Label());
			this->buttonAddProcessorCounter = (gcnew System::Windows::Forms::Button());
			this->buttonAddProcessCounter = (gcnew System::Windows::Forms::Button());
			this->listBoxProcessCounters = (gcnew System::Windows::Forms::ListBox());
			this->listBoxProcessorCounters = (gcnew System::Windows::Forms::ListBox());
			this->labelProcess = (gcnew System::Windows::Forms::Label());
			this->labelProcessCounters = (gcnew System::Windows::Forms::Label());
			this->labelProcessorID = (gcnew System::Windows::Forms::Label());
			this->listBoxAddedPerformanceCounters = (gcnew System::Windows::Forms::ListBox());
			this->labelAddedPerformanceCounters = (gcnew System::Windows::Forms::Label());
			this->numericUpDownProcessorID = (gcnew System::Windows::Forms::NumericUpDown());
			this->buttonStartStop = (gcnew System::Windows::Forms::Button());
			this->textBoxProcessName = (gcnew System::Windows::Forms::TextBox());
			this->buttonClearAddedPerformanceCounters = (gcnew System::Windows::Forms::Button());
			this->buttonSaveAddedPerformanceCounters = (gcnew System::Windows::Forms::Button());
			this->buttonLoadAddedPerformanceCounters = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownProcessorID))->BeginInit();
			this->SuspendLayout();
			// 
			// textBoxMachineName
			// 
			this->textBoxMachineName->Location = System::Drawing::Point(43, 29);
			this->textBoxMachineName->Name = L"textBoxMachineName";
			this->textBoxMachineName->Size = System::Drawing::Size(242, 22);
			this->textBoxMachineName->TabIndex = 0;
			// 
			// labelMachine
			// 
			this->labelMachine->AutoSize = true;
			this->labelMachine->Location = System::Drawing::Point(40, 9);
			this->labelMachine->Name = L"labelMachine";
			this->labelMachine->Size = System::Drawing::Size(61, 17);
			this->labelMachine->TabIndex = 1;
			this->labelMachine->Text = L"Machine";
			// 
			// labelProcessorCounters
			// 
			this->labelProcessorCounters->AutoSize = true;
			this->labelProcessorCounters->Location = System::Drawing::Point(314, 76);
			this->labelProcessorCounters->Name = L"labelProcessorCounters";
			this->labelProcessorCounters->Size = System::Drawing::Size(133, 17);
			this->labelProcessorCounters->TabIndex = 3;
			this->labelProcessorCounters->Text = L"Processor Counters";
			// 
			// buttonAddProcessorCounter
			// 
			this->buttonAddProcessorCounter->Location = System::Drawing::Point(625, 157);
			this->buttonAddProcessorCounter->Name = L"buttonAddProcessorCounter";
			this->buttonAddProcessorCounter->Size = System::Drawing::Size(118, 23);
			this->buttonAddProcessorCounter->TabIndex = 4;
			this->buttonAddProcessorCounter->Text = L"Add";
			this->buttonAddProcessorCounter->UseVisualStyleBackColor = true;
			this->buttonAddProcessorCounter->Click += gcnew System::EventHandler(this, &Form1::buttonAddProcessorCounter_Click);
			// 
			// buttonAddProcessCounter
			// 
			this->buttonAddProcessCounter->Location = System::Drawing::Point(625, 341);
			this->buttonAddProcessCounter->Name = L"buttonAddProcessCounter";
			this->buttonAddProcessCounter->Size = System::Drawing::Size(118, 23);
			this->buttonAddProcessCounter->TabIndex = 5;
			this->buttonAddProcessCounter->Text = L"Add";
			this->buttonAddProcessCounter->UseVisualStyleBackColor = true;
			this->buttonAddProcessCounter->Click += gcnew System::EventHandler(this, &Form1::buttonAddProcessCounter_Click);
			// 
			// listBoxProcessCounters
			// 
			this->listBoxProcessCounters->FormattingEnabled = true;
			this->listBoxProcessCounters->ItemHeight = 16;
			this->listBoxProcessCounters->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"Hello"});
			this->listBoxProcessCounters->Location = System::Drawing::Point(317, 232);
			this->listBoxProcessCounters->Name = L"listBoxProcessCounters";
			this->listBoxProcessCounters->Size = System::Drawing::Size(233, 132);
			this->listBoxProcessCounters->TabIndex = 6;
			// 
			// listBoxProcessorCounters
			// 
			this->listBoxProcessorCounters->FormattingEnabled = true;
			this->listBoxProcessorCounters->ItemHeight = 16;
			this->listBoxProcessorCounters->Location = System::Drawing::Point(317, 96);
			this->listBoxProcessorCounters->Name = L"listBoxProcessorCounters";
			this->listBoxProcessorCounters->Size = System::Drawing::Size(233, 84);
			this->listBoxProcessorCounters->TabIndex = 7;
			// 
			// labelProcess
			// 
			this->labelProcess->AutoSize = true;
			this->labelProcess->Location = System::Drawing::Point(42, 209);
			this->labelProcess->Name = L"labelProcess";
			this->labelProcess->Size = System::Drawing::Size(59, 17);
			this->labelProcess->TabIndex = 8;
			this->labelProcess->Text = L"Process";
			// 
			// labelProcessCounters
			// 
			this->labelProcessCounters->AutoSize = true;
			this->labelProcessCounters->Location = System::Drawing::Point(317, 209);
			this->labelProcessCounters->Name = L"labelProcessCounters";
			this->labelProcessCounters->Size = System::Drawing::Size(120, 17);
			this->labelProcessCounters->TabIndex = 9;
			this->labelProcessCounters->Text = L"Process Counters";
			// 
			// labelProcessorID
			// 
			this->labelProcessorID->AutoSize = true;
			this->labelProcessorID->Location = System::Drawing::Point(42, 76);
			this->labelProcessorID->Name = L"labelProcessorID";
			this->labelProcessorID->Size = System::Drawing::Size(89, 17);
			this->labelProcessorID->TabIndex = 11;
			this->labelProcessorID->Text = L"Processor ID";
			// 
			// listBoxAddedPerformanceCounters
			// 
			this->listBoxAddedPerformanceCounters->FormattingEnabled = true;
			this->listBoxAddedPerformanceCounters->ItemHeight = 16;
			this->listBoxAddedPerformanceCounters->Location = System::Drawing::Point(45, 428);
			this->listBoxAddedPerformanceCounters->Name = L"listBoxAddedPerformanceCounters";
			this->listBoxAddedPerformanceCounters->Size = System::Drawing::Size(499, 84);
			this->listBoxAddedPerformanceCounters->TabIndex = 12;
			// 
			// labelAddedPerformanceCounters
			// 
			this->labelAddedPerformanceCounters->AutoSize = true;
			this->labelAddedPerformanceCounters->Location = System::Drawing::Point(42, 408);
			this->labelAddedPerformanceCounters->Name = L"labelAddedPerformanceCounters";
			this->labelAddedPerformanceCounters->Size = System::Drawing::Size(195, 17);
			this->labelAddedPerformanceCounters->TabIndex = 13;
			this->labelAddedPerformanceCounters->Text = L"Added Performance Counters";
			// 
			// numericUpDownProcessorID
			// 
			this->numericUpDownProcessorID->Location = System::Drawing::Point(45, 97);
			this->numericUpDownProcessorID->Name = L"numericUpDownProcessorID";
			this->numericUpDownProcessorID->ReadOnly = true;
			this->numericUpDownProcessorID->Size = System::Drawing::Size(240, 22);
			this->numericUpDownProcessorID->TabIndex = 14;
			// 
			// buttonStartStop
			// 
			this->buttonStartStop->Location = System::Drawing::Point(317, 533);
			this->buttonStartStop->Name = L"buttonStartStop";
			this->buttonStartStop->Size = System::Drawing::Size(118, 34);
			this->buttonStartStop->TabIndex = 15;
			this->buttonStartStop->Text = L"Start Logging";
			this->buttonStartStop->UseVisualStyleBackColor = true;
			this->buttonStartStop->Click += gcnew System::EventHandler(this, &Form1::buttonStartStop_Click);
			// 
			// textBoxProcessName
			// 
			this->textBoxProcessName->Location = System::Drawing::Point(45, 232);
			this->textBoxProcessName->Name = L"textBoxProcessName";
			this->textBoxProcessName->Size = System::Drawing::Size(240, 22);
			this->textBoxProcessName->TabIndex = 16;
			// 
			// buttonClearAddedPerformanceCounters
			// 
			this->buttonClearAddedPerformanceCounters->Location = System::Drawing::Point(625, 428);
			this->buttonClearAddedPerformanceCounters->Name = L"buttonClearAddedPerformanceCounters";
			this->buttonClearAddedPerformanceCounters->Size = System::Drawing::Size(118, 23);
			this->buttonClearAddedPerformanceCounters->TabIndex = 17;
			this->buttonClearAddedPerformanceCounters->Text = L"Clear";
			this->buttonClearAddedPerformanceCounters->UseVisualStyleBackColor = true;
			this->buttonClearAddedPerformanceCounters->Click += gcnew System::EventHandler(this, &Form1::buttonClearAddedPerformanceCounters_Click);
			// 
			// buttonSaveAddedPerformanceCounters
			// 
			this->buttonSaveAddedPerformanceCounters->Location = System::Drawing::Point(625, 468);
			this->buttonSaveAddedPerformanceCounters->Name = L"buttonSaveAddedPerformanceCounters";
			this->buttonSaveAddedPerformanceCounters->Size = System::Drawing::Size(118, 23);
			this->buttonSaveAddedPerformanceCounters->TabIndex = 18;
			this->buttonSaveAddedPerformanceCounters->Text = L"Save";
			this->buttonSaveAddedPerformanceCounters->UseVisualStyleBackColor = true;
			// 
			// buttonLoadAddedPerformanceCounters
			// 
			this->buttonLoadAddedPerformanceCounters->Location = System::Drawing::Point(625, 509);
			this->buttonLoadAddedPerformanceCounters->Name = L"buttonLoadAddedPerformanceCounters";
			this->buttonLoadAddedPerformanceCounters->Size = System::Drawing::Size(118, 23);
			this->buttonLoadAddedPerformanceCounters->TabIndex = 19;
			this->buttonLoadAddedPerformanceCounters->Text = L"Load";
			this->buttonLoadAddedPerformanceCounters->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(799, 598);
			this->Controls->Add(this->buttonLoadAddedPerformanceCounters);
			this->Controls->Add(this->buttonSaveAddedPerformanceCounters);
			this->Controls->Add(this->buttonClearAddedPerformanceCounters);
			this->Controls->Add(this->textBoxProcessName);
			this->Controls->Add(this->buttonStartStop);
			this->Controls->Add(this->numericUpDownProcessorID);
			this->Controls->Add(this->labelAddedPerformanceCounters);
			this->Controls->Add(this->listBoxAddedPerformanceCounters);
			this->Controls->Add(this->labelProcessorID);
			this->Controls->Add(this->labelProcessCounters);
			this->Controls->Add(this->labelProcess);
			this->Controls->Add(this->listBoxProcessorCounters);
			this->Controls->Add(this->listBoxProcessCounters);
			this->Controls->Add(this->buttonAddProcessCounter);
			this->Controls->Add(this->buttonAddProcessorCounter);
			this->Controls->Add(this->labelProcessorCounters);
			this->Controls->Add(this->labelMachine);
			this->Controls->Add(this->textBoxMachineName);
			this->Name = L"Form1";
			this->Text = L"Performance Counters Logger";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownProcessorID))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void buttonAddProcessCounter_Click(System::Object^  sender, System::EventArgs^  e) {

			 String ^machineName;
			 String ^processName;
			 String ^counterName;

			 if (String::IsNullOrWhiteSpace(textBoxMachineName->Text))
				 machineName = L"localhost";
			 else
				 machineName = textBoxMachineName->Text;

			 if (String::IsNullOrWhiteSpace(textBoxProcessName->Text))
			 {
				 MessageBox::Show("Process name is required");
				 return;
			 }
			 else
			 {
				processName = textBoxProcessName->Text;
			 }

			 if (listBoxProcessCounters->SelectedItems->Count == 0)
			 {
				 MessageBox::Show("Select process counter");
				 return;
			 }
			 else
			 {
				counterName = (String^)(listBoxProcessCounters->SelectedItem);
			 }

			 String^ performanceCounter = "Process," + machineName + "," + processName + "," + counterName + ",";

			 listBoxAddedPerformanceCounters->Items->Add(performanceCounter);

		 }
private: System::Void buttonStartStop_Click(System::Object^  sender, System::EventArgs^  e) {

			 if (LogManager::IsEndLogFlagSet() && listBoxAddedPerformanceCounters->Items->Count > 0)
			 {
				LogManager::ResetEndLogFlag();

				std::vector<std::string>  addedCounters;

				for (int ii = 0; ii < listBoxAddedPerformanceCounters->Items->Count; ii++)
				{
					String ^ms = (String ^)listBoxAddedPerformanceCounters->Items[ii];
					std::string ns = msclr::interop::marshal_as<std::string>(ms);
					addedCounters.push_back(ns);
				}

				logManager->BeginLog(addedCounters);
				this->buttonStartStop->Text = L"Stop Logging";
				this->buttonStartStop->ForeColor = System::Drawing::Color::Green; 

				buttonAddProcessorCounter->Enabled = false;
				buttonAddProcessCounter->Enabled = false;
				buttonClearAddedPerformanceCounters->Enabled = false;
				buttonSaveAddedPerformanceCounters->Enabled = false;
				buttonLoadAddedPerformanceCounters->Enabled = false;
			 }
			 else
			 {
				 LogManager::SetEndLogFlag();
				 this->buttonStartStop->Text = L"Start Logging";
				 this->buttonStartStop->ForeColor = System::Drawing::Color::Black; 

				buttonAddProcessorCounter->Enabled = true;
				buttonAddProcessCounter->Enabled = true;
				buttonClearAddedPerformanceCounters->Enabled = true;
				buttonSaveAddedPerformanceCounters->Enabled = true;
				buttonLoadAddedPerformanceCounters->Enabled = true;
			 }
		 }
private: System::Void buttonAddProcessorCounter_Click(System::Object^  sender, System::EventArgs^  e) {
			String ^machineName;
			 String ^processorNumber;
			 String ^counterName;

			 if (String::IsNullOrWhiteSpace(textBoxMachineName->Text))
			 {
				 MessageBox::Show("Machine field should not be empty");
			 }
			 else
				 machineName = textBoxMachineName->Text;

			 processorNumber = Convert::ToString(numericUpDownProcessorID->Value);

			 if (listBoxProcessorCounters->SelectedItems->Count == 0)
			 {
				 MessageBox::Show("Select processor counter");
				 return;
			 }
			 else
			 {
				counterName = (String^)(listBoxProcessorCounters->SelectedItem);
			 }

			 String^ performanceCounter = "Processor," + machineName + "," + processorNumber + "," + counterName + ",";

			 listBoxAddedPerformanceCounters->Items->Add(performanceCounter);

		 }

private:	int PopulateProcessCounters()
			{
				this->listBoxProcessCounters->Items->Clear();

				std::vector<std::string> list = logManager->GetListOfProcessCounters();

				for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it)
				{
					this->listBoxProcessCounters->Items->Add(gcnew String((*it).c_str()));
				}

				int count = list.size();

				return count;
			}

private:	int PopulateProcessorCounter()
			{
				this->listBoxProcessorCounters->Items->Clear();

				std::vector<std::string> list = logManager->GetListOfProcessorCounters();

				for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it)
				{
					this->listBoxProcessorCounters->Items->Add(gcnew String((*it).c_str()));
				}

				int count = list.size();

				return count;

				return 0;
			}
private: System::Void buttonClearAddedPerformanceCounters_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (listBoxAddedPerformanceCounters->SelectedIndex >= 0)
			 {
				 listBoxAddedPerformanceCounters->Items->RemoveAt(listBoxAddedPerformanceCounters->SelectedIndex);
				 listBoxAddedPerformanceCounters->ClearSelected();
			 }
		 }
};
}

