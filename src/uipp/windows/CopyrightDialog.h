#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "DXApplication.h"

namespace dxui
{
	/// <summary> 
	/// Summary for CopyrightDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class CopyrightDialog : public System::Windows::Forms::Form
	{
	public: 
		CopyrightDialog(void)
		{
			InitializeComponent();
			this->timer = new Timer();
			this->timer->Interval = 15000;
			this->timer->Tick += new EventHandler(this, &dxui::CopyrightDialog::closeDialog);
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

	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Label *  CopyText;
	private: System::Windows::Forms::Timer * timer;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(dxui::CopyrightDialog));
			this->CopyText = new System::Windows::Forms::Label();
			this->button1 = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// CopyText
			// 
			this->CopyText->Font = new System::Drawing::Font(S"Times New Roman", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->CopyText->Location = System::Drawing::Point(0, 245);
			this->CopyText->Name = S"CopyText";
			this->CopyText->Size = System::Drawing::Size(314, 64);
			this->CopyText->TabIndex = 0;
			this->CopyText->Text = S"label1";
			this->CopyText->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// button1
			// 
			this->button1->Image = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"button1.Image")));
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(315, 240);
			this->button1->TabIndex = 2;
			this->button1->Click += new System::EventHandler(this, &dxui::CopyrightDialog::closeDialog);
			// 
			// CopyrightDialog
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(315, 313);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->CopyText);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"CopyrightDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"CopyrightDialog";
			this->Load += new System::EventHandler(this, &dxui::CopyrightDialog::CopyrightDialog_Load);
			this->ResumeLayout(false);

		}		

	public: 
		void setText(const char *t) {
			this->CopyText->Text = new System::String(t);
		}
		void showIt() {
			theDXApplication->getMainForm()->AddOwnedForm(this);
			this->ShowInTaskbar = false;
			this->Show();
			this->timer->Start();
		}

	private: System::Void closeDialog(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->timer->Stop();
				 this->Close();
			 }

	private: System::Void CopyrightDialog_Load(System::Object *  sender, System::EventArgs *  e)
			 {
			 }

	};
}