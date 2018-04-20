#include "BlockChain.h"

inline BlockChain::BlockChain(const char *s)
{
	head = new Block(s);
}

inline int BlockChain::GetLen()const
{
	if (head)
		return head->GetLen();
	else
		return 0;
}

inline BlockChain::operator MyString() const
{
	char *s = new char[GetLen() + 1];
	head->Copy(s);
	MyString str = s;
	delete[] s;
	return str;
}

inline Block::Block()
{
	data[0] = '\0';
	next = NULL;
}

inline Block::Block(const char *s)
{
	int i;
	for (i = 0; i < BLOCKSIZE && *s; i++) {
		data[i] = *s++;
	}
	if (i == BLOCKSIZE)
		next = new Block(s + i);
}

inline int Block::GetLen()const
{
	int len = 0;
	for (int i = 0; i < BLOCKSIZE; i++) {
		switch (data[i]) {
		case '#':break;
		case '\0':return len;
		default:len++;
		}
	}
	return next->GetLen();
}

inline void Block::Copy(char *s) const
{
	for (int i = 0; i < BLOCKSIZE; i++) {
		switch (data[i]) {
		case '#':break;
		case '\0':
			*s++ = '\0';
			return;
			break;
		default:
			*s++ = data[i];
		}
	}
	next->Copy(s);
}

inline Block::~Block()
{
	if (next)
		delete next;
}