#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "DXApplication.h"

#ifdef GetObject
#undef GetObject
#endif

namespace dxui
{
	/// <summary> 
	/// Summary for MsgWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class MsgWindow : public System::Windows::Forms::Form
	{
	public: 
		MsgWindow(void)
		{
			InitializeComponent();
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  Close;
	private: System::Windows::Forms::TextBox *  messageBox;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(dxui::MsgWindow));
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->Close = new System::Windows::Forms::MenuItem();
			this->messageBox = new System::Windows::Forms::TextBox();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__1[0] = this->menuItem1;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__2[0] = this->Close;
			this->menuItem1->MenuItems->AddRange(__mcTemp__2);
			this->menuItem1->Text = S"&File";
			// 
			// Close
			// 
			this->Close->Index = 0;
			this->Close->Shortcut = System::Windows::Forms::Shortcut::CtrlW;
			this->Close->Text = S"&Close";
			// 
			// messageBox
			// 
			this->messageBox->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->messageBox->Location = System::Drawing::Point(0, 0);
			this->messageBox->Multiline = true;
			this->messageBox->Name = S"messageBox";
			this->messageBox->ReadOnly = true;
			this->messageBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->messageBox->Size = System::Drawing::Size(576, 285);
			this->messageBox->TabIndex = 0;
			this->messageBox->Text = S"Welcome!";
			this->messageBox->WordWrap = false;
			// 
			// MsgWindow
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(576, 285);
			this->Controls->Add(this->messageBox);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Menu = this->mainMenu1;
			this->MinimumSize = System::Drawing::Size(312, 120);
			this->Name = S"MsgWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"Message Window";
			this->Load += new System::EventHandler(this, &dxui::MsgWindow::MsgWindow_Load);
			this->ResumeLayout(false);

		}		
	private: System::Void MsgWindow_Load(System::Object *  sender, System::EventArgs *  e)
			 {
			 }
	public: void SetText(const char *t) {
				this->messageBox->AppendText(System::String::Concat(new System::String(t), System::Environment::NewLine));
			}
			void SetText(const char *t, const char *t2, const char *t3) {
				System::String * s = new System::String(t);
				s = System::String::Concat(s, new System::String(t2), new System::String(t3), System::Environment::NewLine);
				this->messageBox->AppendText(s);
			}
			void Clear() {
				this->messageBox->Clear();
			}
			void showIt() {
				this->ShowInTaskbar = false;
				this->Show();
			}


	};
}