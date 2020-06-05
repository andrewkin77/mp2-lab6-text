#ifndef _TextLink_h_
#define _TextLink_h_

#include<string>

#define TTextLineLength 80 //setting limit for line length
#define MemSize 100

class TText;
class TTextLink;

typedef char TStr[TTextLineLength]; //for convenience


struct TTextMem
{
	TTextLink* pFirst;
	TTextLink* pLast;
	TTextLink* pFree;
	friend class TTextLink;
};

// text links objects
class TTextLink
{
public:
	TTextLink *pNext, *pDown;
	TStr str;
	static TTextMem MemHeader; //memmory managment system

	//constructor and destructor
	TTextLink(const TStr c=nullptr, TTextLink *_pNext = nullptr,TTextLink *_pDown = nullptr);
	~TTextLink();


	static void InitMemSystem(int size = MemSize); //memmory initialization
	static void PrintFreeLink(void);
	void* operator new (size_t size);
	void operator delete (void* pM);
	static void MemCleaner(TText& txt);
};
#endif