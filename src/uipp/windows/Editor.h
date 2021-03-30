
#pragma once

#ifdef GetObject
#undef GetObject
#endif

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class Network;

#include "List.h"
#include "Command.h"
#include "ControlPanel.h"
#include "Cacheability.h"
#include "InsertNetworkDialog.h"
#include "Stack.h"
#include "OpenFileCommand.h"

typedef long NodeStatusChange;

#define ClassEditorWindow "EditorWindow"

namespace dxui
{

	/// <summary> 
	/// Summary for Editor
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Editor : public System::Windows::Forms::Form
	{
	protected:
		Network*			network;

	// Constructors
	public: 
		Editor(void)
		{
			InitializeComponent();
		}
		Editor(bool isAnchor, Network *network)
		{
			ASSERT(network);
			this->network = network;
			InitializeComponent();
			if(this->network->getFileName() == NULL)
				this->Text = S"Visual Program Editor";
			else
				this->Text = System::String::Concat(S"Visual Program Editor - ", 
					new System::String(this->network->getFileName()));
			if(!isAnchor)
				this->RecentPrograms->Enabled = false;
			this->updateRecentNets();
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
	private: System::Windows::Forms::MenuItem *  New;
	private: System::Windows::Forms::MenuItem *  Open;
	private: System::Windows::Forms::MenuItem *  Quit;
	private: System::Windows::Forms::MenuItem *  File;
	private: System::Windows::Forms::MenuItem *  Edit;
	private: System::Windows::Forms::MenuItem *  Execute;
	private: System::Windows::Forms::MenuItem *  ExecuteOnce;
	private: System::Windows::Forms::MenuItem *  Windows;
	private: System::Windows::Forms::MenuItem *  Connection;
	private: System::Windows::Forms::MenuItem *  Options;
	private: System::Windows::Forms::MenuItem *  Help;
	private: System::Windows::Forms::MenuItem *  ContextSensitiveHelp;
	private: System::Windows::Forms::MenuItem *  About;
	private: System::Windows::Forms::MenuItem *  Sep1;
	private: System::Windows::Forms::MenuItem *  Sep2;

	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TreeView *  treeView1;
	private: System::Windows::Forms::TabControl *  tabControl2;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::GroupBox *  groupBox1;

	private:
		List* executed_nodes;
	private: System::Windows::Forms::TabControl *  ToolsTab;
	private: System::Windows::Forms::MenuItem *  RecentPrograms;





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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(dxui::Editor));
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->File = new System::Windows::Forms::MenuItem();
			this->New = new System::Windows::Forms::MenuItem();
			this->Open = new System::Windows::Forms::MenuItem();
			this->RecentPrograms = new System::Windows::Forms::MenuItem();
			this->Sep1 = new System::Windows::Forms::MenuItem();
			this->Quit = new System::Windows::Forms::MenuItem();
			this->Edit = new System::Windows::Forms::MenuItem();
			this->Execute = new System::Windows::Forms::MenuItem();
			this->ExecuteOnce = new System::Windows::Forms::MenuItem();
			this->Windows = new System::Windows::Forms::MenuItem();
			this->Connection = new System::Windows::Forms::MenuItem();
			this->Options = new System::Windows::Forms::MenuItem();
			this->Help = new System::Windows::Forms::MenuItem();
			this->ContextSensitiveHelp = new System::Windows::Forms::MenuItem();
			this->Sep2 = new System::Windows::Forms::MenuItem();
			this->About = new System::Windows::Forms::MenuItem();
			this->ToolsTab = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->treeView1 = new System::Windows::Forms::TreeView();
			this->tabControl2 = new System::Windows::Forms::TabControl();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->ToolsTab->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[7];
			__mcTemp__1[0] = this->File;
			__mcTemp__1[1] = this->Edit;
			__mcTemp__1[2] = this->Execute;
			__mcTemp__1[3] = this->Windows;
			__mcTemp__1[4] = this->Connection;
			__mcTemp__1[5] = this->Options;
			__mcTemp__1[6] = this->Help;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// File
			// 
			this->File->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__2[0] = this->New;
			__mcTemp__2[1] = this->Open;
			__mcTemp__2[2] = this->RecentPrograms;
			__mcTemp__2[3] = this->Sep1;
			__mcTemp__2[4] = this->Quit;
			this->File->MenuItems->AddRange(__mcTemp__2);
			this->File->Text = S"&File";
			// 
			// New
			// 
			this->New->Index = 0;
			this->New->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->New->Text = S"&New";
			this->New->Click += new System::EventHandler(this, &dxui::Editor::NewClick);
			// 
			// Open
			// 
			this->Open->Index = 1;
			this->Open->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
			this->Open->Text = S"&Open";
			this->Open->Click += new System::EventHandler(this, &dxui::Editor::OpenClick);
			// 
			// RecentPrograms
			// 
			this->RecentPrograms->Index = 2;
			this->RecentPrograms->Text = S"Re&cent Programs";
			// 
			// Sep1
			// 
			this->Sep1->Index = 3;
			this->Sep1->Text = S"-";
			// 
			// Quit
			// 
			this->Quit->Index = 4;
			this->Quit->Shortcut = System::Windows::Forms::Shortcut::CtrlQ;
			this->Quit->Text = S"&Quit";
			this->Quit->Click += new System::EventHandler(this, &dxui::Editor::Quit_Click);
			// 
			// Edit
			// 
			this->Edit->Index = 1;
			this->Edit->Text = S"&Edit";
			this->Edit->Click += new System::EventHandler(this, &dxui::Editor::menuItem6_Click);
			// 
			// Execute
			// 
			this->Execute->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__3[0] = this->ExecuteOnce;
			this->Execute->MenuItems->AddRange(__mcTemp__3);
			this->Execute->Text = S"E&xecute";
			// 
			// ExecuteOnce
			// 
			this->ExecuteOnce->Index = 0;
			this->ExecuteOnce->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
			this->ExecuteOnce->Text = S"Execute &Once";
			this->ExecuteOnce->Click += new System::EventHandler(this, &dxui::Editor::ExecuteOnce_Click);
			// 
			// Windows
			// 
			this->Windows->Index = 3;
			this->Windows->Text = S"&Windows";
			// 
			// Connection
			// 
			this->Connection->Index = 4;
			this->Connection->Text = S"&Connection";
			// 
			// Options
			// 
			this->Options->Index = 5;
			this->Options->Text = S"&Options";
			// 
			// Help
			// 
			this->Help->Index = 6;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__4[0] = this->ContextSensitiveHelp;
			__mcTemp__4[1] = this->Sep2;
			__mcTemp__4[2] = this->About;
			this->Help->MenuItems->AddRange(__mcTemp__4);
			this->Help->Text = S"&Help";
			// 
			// ContextSensitiveHelp
			// 
			this->ContextSensitiveHelp->Index = 0;
			this->ContextSensitiveHelp->Shortcut = System::Windows::Forms::Shortcut::F1;
			this->ContextSensitiveHelp->Text = S"&Context-Sensitive Help";
			// 
			// Sep2
			// 
			this->Sep2->Index = 1;
			this->Sep2->Text = S"-";
			// 
			// About
			// 
			this->About->Index = 2;
			this->About->Text = S"&About";
			// 
			// ToolsTab
			// 
			this->ToolsTab->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left);
			this->ToolsTab->Controls->Add(this->tabPage1);
			this->ToolsTab->Location = System::Drawing::Point(4, 10);
			this->ToolsTab->Name = S"ToolsTab";
			this->ToolsTab->SelectedIndex = 0;
			this->ToolsTab->Size = System::Drawing::Size(175, 465);
			this->ToolsTab->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->treeView1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(167, 439);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Tools";
			// 
			// treeView1
			// 
			this->treeView1->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->treeView1->BackColor = System::Drawing::SystemColors::Menu;
			this->treeView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeView1->ImageIndex = -1;
			this->treeView1->Location = System::Drawing::Point(0, 0);
			this->treeView1->Name = S"treeView1";
			System::Windows::Forms::TreeNode* __mcTemp__5[] = new System::Windows::Forms::TreeNode*[1];
			__mcTemp__5[0] = new System::Windows::Forms::TreeNode(S"( ALL )");
			this->treeView1->Nodes->AddRange(__mcTemp__5);
			this->treeView1->SelectedImageIndex = -1;
			this->treeView1->Size = System::Drawing::Size(164, 441);
			this->treeView1->TabIndex = 0;
			// 
			// tabControl2
			// 
			this->tabControl2->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->tabControl2->Controls->Add(this->tabPage2);
			this->tabControl2->Location = System::Drawing::Point(181, 10);
			this->tabControl2->Name = S"tabControl2";
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(517, 465);
			this->tabControl2->TabIndex = 1;
			this->tabControl2->SelectedIndexChanged += new System::EventHandler(this, &dxui::Editor::tabControl2_SelectedIndexChanged);
			// 
			// tabPage2
			// 
			this->tabPage2->AutoScroll = true;
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(509, 439);
			this->tabPage2->TabIndex = 0;
			this->tabPage2->Text = S"Untitled";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(702, 481);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			// 
			// Editor
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(704, 481);
			this->Controls->Add(this->tabControl2);
			this->Controls->Add(this->ToolsTab);
			this->Controls->Add(this->groupBox1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Menu = this->mainMenu1;
			this->MinimumSize = System::Drawing::Size(320, 320);
			this->Name = S"Editor";
			this->Text = S"Visual Program Editor";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, &dxui::Editor::Editor_Closing);
			this->Load += new System::EventHandler(this, &dxui::Editor::Editor_Load);
			this->ToolsTab->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabControl2->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	private: System::Void Editor_Load(System::Object *  sender, System::EventArgs *  e)
			 {
			 }

private: System::Void menuItem6_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void tabControl2_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void Quit_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 theDXApplication->exitCmd->execute();
		 }

private: System::Void Editor_Closing(System::Object * sender, System::ComponentModel::CancelEventArgs * e)
		 {
			 e->Cancel = true;
			 theDXApplication->exitCmd->execute();
		 }
private: System::Void ExecuteOnce_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 theDXApplication->executeOnceCmd->execute();
		 }

private: System::Void OpenClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 theDXApplication->openFileCmd->execute();
			 if(this->network->getFileName() != NULL)
				 this->Text = System::String::Concat(S"Visual Program Editor - ", 
					new System::String(this->network->getFileName()));
		 }

private: System::Void NewClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->network->getNewCommand()->execute();
			 this->Text = S"Visual Program Editor";

		 }
private: System::Void OpenRecentFileClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 Command * cmd;
			 System::Windows::Forms::MenuItem *sel = 
				 static_cast<System::Windows::Forms::MenuItem *> (sender);
			 List recent_nets;
			 theDXApplication->getRecentNets(recent_nets);
			 ListIterator iter(recent_nets);
			 Symbol s;
			 for(int i=0; i< sel->Index+1; i++)
				 s = (Symbol)(long)iter.getNext();
			 cmd = new OpenFileCommand(s);
			 cmd->execute();
			 if(this->network->getFileName() != NULL)
				 this->Text = System::String::Concat(S"Visual Program Editor - ", 
				 new System::String(this->network->getFileName()));
			 delete cmd;
		 }

// Update the Recent Programs File menu item with the list
// stored internally.
private: void updateRecentNets() {
			char fname[256];
			if(theIBMApplication->getApplicationDefaultsFileName(fname)) {
				List recent_nets;
				List baseNames;
				theDXApplication->getRecentNets(recent_nets);
				int numNets = recent_nets.getSize();
				if(numNets == 0) {
					this->RecentPrograms->Enabled = false;
				} else {
					System::Windows::Forms::MenuItem * progs[] = 
						new System::Windows::Forms::MenuItem*[numNets];
					ListIterator iter(recent_nets);
					Symbol s;
					Command *cmd;
					int i = 0;
					while(s=(Symbol)(long)iter.getNext()) {
						const char* fullpath = theSymbolManager->getSymbolString(s);
						char *cp = GetFileBaseName(fullpath, 0);
						baseNames.appendElement(cp);
						bool unique = true;
						ListIterator biter(baseNames);
						const char* cmprtr;
						while(cmprtr = (const char*)biter.getNext()) {
							if((cmprtr!=cp) && (EqualString(cmprtr, cp))) {
								unique = false;
								break;
							}
						}
						if(!unique) {
							cp = DuplicateString(fullpath);
							baseNames.appendElement(cp);
						}
						progs[i] = new System::Windows::Forms::MenuItem();
						progs[i]->Index = i;
						progs[i]->Text = new System::String(cp);
						progs[i]->Click += new System::EventHandler(this, &dxui::Editor::OpenRecentFileClick);
						i++;
						//bi->setLabel(cp);
					}
					this->RecentPrograms->MenuItems->AddRange(progs);
					iter.setList(baseNames);
					char *cp;
					while(cp=(char *)iter.getNext()) delete [] cp;
				}
			}
			else
				this->RecentPrograms->Enabled = false;
		 }
};
}

