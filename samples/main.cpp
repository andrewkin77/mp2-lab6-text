#include "Text.h"
#include <fstream>
#include <iostream>
using namespace std;

TTextMem TTextLink::MemHeader;

int main()
{
  try
  {
    TTextLink::InitMemSystem();
    string help = "'set' - change current line\nType 'next' - go to next line  ";
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    cout << endl;
    TText t;
    t.Read(file_name);
    bool saved = true; //if there are unsaved changes
    bool run = true; //stopping condition
    bool deleted = false; //if anything gets deleted (for optimized garbage collection)
    TTextLink* curr_line = t.GetLink();


    //main loop
    while (run)
    {   
        string cmd; //user input
        bool OK = false; //command check

        cout << "Current file: " << file_name << endl;

        //printing text
        cout << "-----Start-of-file-----" << endl;
        t.cPrint(curr_line);
        cout << "------End-of-file------\n" << endl;

        //user prompt
        cout << "What do you want to do next?\n" << endl;
        getline(cin >> ws, cmd); //input strings with spaces
        //cout << endl;

        //SetLine
        if(cmd == "set")
        {
          cout << "Enter new line: ";
          string line;
          getline(cin >> ws, line);
          cout << endl;
          t.SetLine(line);
          OK = true;
          saved = false;
        }

        //GoFirstLink
        if(cmd == "first")
        {
          if (deleted) // check if there is garbage
          {
            TTextLink::MemCleaner(t); //background garbage collection
            cout << "Garbage collected!" << endl;
            deleted = false;
          }
          t.GoFirstLink();
          curr_line = t.GetLink();
          OK = true;
        }

        //GoNextLink
        if(cmd == "next")
        {
          t.GoNextLink();
          curr_line = t.GetLink();
          OK = true;
        }

        //GoPrevLink
        if(cmd == "prev")
        {
          t.GoPrevLink();
          curr_line = t.GetLink();
          OK = true;
        }

        //GoDownLink
        if(cmd == "down")
        {
          t.GoDownLink();
          curr_line = t.GetLink();
          OK = true;
        }

        //InsNextLine
        if(cmd == "ins next line")
        {
          cout << "Enter new line: ";
          string line;
          getline(cin >> ws, line);
          cout << endl;
          t.InsNextLine(line);
          OK = true;
          saved = false;
        }

        //InsDownLine
        if(cmd == "ins down line")
        {
          cout << "Enter new line: ";
          string line;
          getline(cin >> ws, line);
          cout << endl;
          t.InsDownLine(line);
          OK = true;
          saved = false;
        }

        //InsNextSection
        if(cmd == "ins next section")
        {
          cout << "Enter new line: ";
          string line;
          getline(cin >> ws, line);
          cout << endl;
          t.InsNextSection(line);
          OK = true;
          saved = false;
        }

        //InsDownSection
        if(cmd == "ins down section")
        {
          cout << "Enter new line: ";
          string line;
          getline(cin >> ws, line);
          cout << endl;
          t.InsDownSection(line);
          OK = true;
          saved = false;
        }

        //DelNext
        if(cmd == "del next")
        {
          t.DelNext();
          cout << "Next link deleted\n" << endl; 
          OK = true;
          saved = false;
          deleted = true;
        }

        //DelDown
        if(cmd == "del down")
        {
          t.DelDown();
          cout << "Down link deleted\n" << endl; 
          OK = true;
          saved = false;
          deleted = true;
        }

        //save in the same file
        if (cmd == "save")
        {
          t.Save(file_name);
          cout << "\x1b[32m" <<"Complete!\n" << "\x1b[39m" << endl;
          OK = true;
          saved = true;
        }

        //save in a different file
        if (cmd == "save as")
        {
          string save_file;
          cout << "Enter file name: ";
          cin >> save_file;
          cout << endl;
          t.Save(save_file);
          cout << "\x1b[32m" <<"Complete!\n" << "\x1b[39m" << endl;
          OK = true;
          saved = true;
        }

        //print free links
        if (cmd == "print free")
        {
          TTextLink::PrintFreeLink();
          OK = true;
        }

        //collect garbage


        //list of availible commands
        if (cmd == "help")
        {
          cout << "'set' - change current line\n" << endl;
          cout << "'next' - go to the next line\n" << endl;
          cout << "'first' - go to the first line\n" << endl;
          cout << "'prev' - go to the previous line\n" << endl;
          cout << "'down' - go inside current section\n" << endl;
          cout << "'ins next line' - insert line between current and next\n" << endl;
          cout << "'ins down line' - insert line between current and down\n" << endl;
          cout << "'ins next section' - insert new section next to the current line\n" << endl;
          cout << "'ins down section' - insert new section down from the current line\n" << endl;
          cout << "'del next' - delete next line\n" << endl;
          cout << "'del down' - delete down line\n" << endl;
          cout << "'save' - save text in the same file\n" << endl;
          cout << "'save as' - save text in a different file\n" << endl;
          cout << "'print free' - print free links\n" << endl;
          cout << "'exit' - exit programm\n" << endl;
          OK = true;
        }

        //exit programm
        if(cmd == "exit")
        {
          if (!saved)
          {
            cout << "You have unsaved changes" << endl;
            cout << "Would you like to save them? yes/no" << endl;
            cin >> cmd;
            if (cmd == "yes")
            {
              t.Save(file_name);
            }
              run = false;
          }
          else
          {
            run = false;
          }
          OK = true;
        }

        //if non of the above
        if (!OK)
        {
          cout << "Error! " << cmd <<": command not found." << endl;
          cout << "Type 'help' to see all availible commands\n" << endl;
        }

    } //end while 
    TTextLink::MemCleaner(t);

  } //end of try

  catch(const char* ex)
  {
      cout << "Critical Error!" << endl << ex << endl;
  }

}
        // i = 1;
        // for (t.Reset(); !t.IsEnd(); t.GoNext())
        // { 
        //   string str = to_string(i) + " " + t.GetLine().substr(2);
        //   t.SetLine(str);
        //   if (str[0] == curr_line[0])
        //     cout << str << " <- You are here :D" << endl;
        //   else
        //      cout << str << endl;
        //   i++;
        // }

        // //open new file
        // if (cmd == "new file")
        // {
        //   cout << "Enter new file name: ";
        //   string fn;
        //   getline(cin >> ws, fn);
        //   cout << endl;
        //   t.Read(fn);
        //   file_name = fn;
        //   OK = true;
        //   saved = false;
        // }