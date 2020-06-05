#include "Text.h"
#include <fstream>
#include <iostream>
using namespace std;


TText::TText()
{
	pFirst = pCurr = pPrev = nullptr;
}

TText::~TText()
{

}

void TText::GoFirstLink()
{
	pCurr = pFirst;
	stack.clear();
}

void TText::GoDownLink()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}
	if (!pCurr->pDown)
	{
		cout << "\nError! Down line doesn't exist\n" << endl;
		return;
	}
	stack.push(pCurr);
	pCurr = pCurr->pDown;
}

void TText::GoNextLink()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	if (!pCurr->pNext)
	{
		cout << "\nError! Next line doesn't exist\n" << endl;
		return;
	}
	stack.push(pCurr);
	pCurr = pCurr->pNext;
}

void TText::GoPrevLink()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	if(stack.IsEmpty())
		return;

	pCurr = stack.pop();
}

void TText::SetLine(string str)
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}
	
	strcpy(pCurr->str, str.c_str());
}

string TText::GetLine()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	return string(pCurr->str);
}

TTextLink* TText::GetLink()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	return pCurr;
}

void TText::InsNextLine(string str)
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	TTextLink *tmp = new TTextLink(str.c_str());
	tmp->pNext = pCurr->pNext;
	pCurr->pNext = tmp;
}

void TText::InsDownLine(string str)
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	TTextLink *tmp = new TTextLink(str.c_str());
	tmp->pNext = pCurr->pDown;
	pCurr->pDown = tmp;
}

void TText::InsNextSection(string str)
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	TTextLink *tmp = new TTextLink(str.c_str());
	tmp->pDown = pCurr->pNext;
	pCurr->pNext = tmp;
}

void TText::InsDownSection(string str)
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	TTextLink *tmp = new TTextLink(str.c_str());
	tmp->pDown = pCurr->pDown;
	pCurr->pDown = tmp;
}

void TText::DelNext()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	if(!pCurr->pNext)
		return;

	TTextLink* tmp = pCurr->pNext;
	pCurr->pNext = tmp->pNext;
	delete tmp;
}

void TText::DelDown()
{
	if(!pCurr)
	{
		const char ex[] = "pCurr is null";
		throw ex;
	}

	if(!pCurr->pDown)
		return;

	TTextLink* tmp = pCurr->pDown;
	pCurr->pDown = tmp->pNext;
	delete tmp;
}

void TText::Read(string fn)
{
	ifstream ifs(fn);
	pFirst = ReadRec(ifs);
	pCurr = pFirst;
}

TTextLink* TText::ReadRec(ifstream& ifs)
{
	TTextLink *tmp, *pHead, *p;
	pHead = p = nullptr;
	char str[81];
	while(!ifs.eof())
	{
		ifs.getline(str, 80,'\n');

		if(str[0] == '}')
			break;

		else if(str[0] == '{')
			p->pDown = ReadRec(ifs);

		else
		{
			tmp = new TTextLink(str);
			if(!pHead)
				pHead = p = tmp;

			else
			{
				p->pNext = tmp;
				p = p->pNext;
			}
		}
	}
	return pHead;
}

void TText::Save(string fn)
{	
	string ind = ""; //indentation
	ofstream ofs(fn);
	SaveSec(ofs, pFirst, ind);
}

void TText::SaveSec(ofstream& ofs, TTextLink* p, string ind)
{	
	ofs << ind << p->str << endl;
	if (p->pDown)
	{
		ofs << ind << '{' << endl;
		SaveSec(ofs, p->pDown, ind + "    ");
		ofs << ind << '}' << endl;
	}
	if (p->pNext)
		SaveSec(ofs, p->pNext, ind);
}

void TText::cPrint(TTextLink* curr_line)
{	
	string ind = ""; //indentation
	cPrintSec(pFirst, curr_line, ind);
}

void TText::cPrintSec(TTextLink* p, TTextLink* curr_line, string ind)
{	
	if (p == curr_line)
	{
	cout << ind << p->str <<  "\x1b[36m" << " <- You are here! :D" << "\x1b[39m" << endl;
	}
	else
	{
		cout << ind << p->str << endl;
	}

	if (p->pDown)
	{
		cout << ind << '{' << endl;
		cPrintSec(p->pDown, curr_line, ind + "    ");
		cout << ind << '}' << endl;
	}
	if (p->pNext)
		cPrintSec(p->pNext, curr_line, ind);
}

void TText::Reset()
{
	stack.clear();
	
	pCurr = pFirst;
	if (pCurr)
	{
		stack.push(pCurr);
		if (pCurr->pNext)
			stack.push(pCurr->pNext);

		if (pCurr->pDown)
			stack.push(pCurr->pDown);
	}
}

bool TText::IsEnd()
{
	return stack.IsEmpty();
}

void TText::GoNext()
{

	pCurr = stack.pop();
	if (pCurr != pFirst)
	{
		if (pCurr->pNext)
			stack.push(pCurr->pNext);

		if (pCurr->pDown)
			stack.push(pCurr->pDown);
	}
		
}