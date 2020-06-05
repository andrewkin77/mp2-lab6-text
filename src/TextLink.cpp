#include"TextLink.h"
#include"Text.h"
#include <iostream>
using namespace std;

TTextLink::TTextLink(const TStr c, TTextLink *_pNext,TTextLink *_pDown){
	pNext = _pNext;
	pDown = _pDown;
	if (!c)
	{
		str[0] = '\0';
	} 
	else
	{
		strcpy(str, c);
	}
}

TTextLink::~TTextLink()
{

}

void TTextLink::InitMemSystem(int size)
{
	MemHeader.pFirst = (TTextLink*) new char[sizeof(TTextLink)*size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	TTextLink* pLink = MemHeader.pFirst;

	for (int i = 0; i < size - 1; i++)
	{
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}

	pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink(void)
{
	cout << "List of free links" << endl;
	int count = 0;

	for (TTextLink* pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext)
	{	
		if (pLink->str[0] != '\0')
		{
			cout << pLink->str << endl;
		}
		count++;
	}
	cout << "Number of free links: " << count << endl <<endl;
}

void * TTextLink::operator new(size_t size)
{
	TTextLink* pLink = MemHeader.pFree;
	if (MemHeader.pFree)
	{
		MemHeader.pFree = pLink->pNext;
	}
	return pLink;
}

void TTextLink::operator delete(void * pM)
{
	TTextLink* pLink = (TTextLink*)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

void TTextLink::MemCleaner(TText& txt)
{
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
	{
		string tmp = "&&&";
		tmp += txt.GetLine();
		txt.SetLine(tmp);
	}

	TTextLink* pLink;
	for (pLink = MemHeader.pFree; pLink != NULL; pLink = pLink->pNext)
	{
		strcpy(pLink->str, "&&&");
	}

	for (pLink = MemHeader.pFirst; pLink <= MemHeader.pLast; pLink++)
	{
		if (strstr(pLink->str, "&&&"))
		{
			strcpy(pLink->str, pLink->str + 3); 
		} 
		else
		{
			delete pLink;
		}
	}
}
