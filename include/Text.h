#ifndef _Text_h_
#define _Text_h_

#include"TextLink.h"
#include "stack.h"
using namespace std;

class TText{
private:
	TTextLink *pFirst, *pCurr, *pPrev;
	TStack<TTextLink*> stack;
public:

	//construcor and destructor
	TText();
	~TText();

	//text navigation
	void GoFirstLink();
	void GoDownLink();
	void GoNextLink();
	void GoPrevLink();

	//adding/redacting lines
	void SetLine(string str);
	TTextLink* GetLink();
	string GetLine();
	void InsNextLine(string str);
	void InsDownLine(string str);
	void InsNextSection(string str);
	void InsDownSection(string str);

	//deleting lines
	void DelNext();
	void DelDown();

	//read from file
	void Read(string fn);
	TTextLink* ReadRec(ifstream& ifs);

	//save in a file
	void Save(string fn);
	void SaveSec(ofstream& ofs, TTextLink* p, string ind);

	//print into console
	void cPrint(TTextLink* curr_line); 
	void cPrintSec(TTextLink* p, TTextLink* curr_line, string ind);

	void Reset();
	bool IsEnd();
	void GoNext();
};
#endif