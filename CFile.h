#pragma once
#include <iostream>

using namespace std;

class CFile
{
public:
	CFile();
	CFile(const char *filename,const char *creation_date, int size);
	CFile(const CFile &file);
	~CFile();

	void rename(const char*);
	void parseFrom(char *str);

	CFile& operator= (const CFile &file);
	bool operator!=(const CFile &file);
	friend ostream& operator<<(ostream& stream, CFile &obj);

	bool isAfter(const char *time);

	const char *getFilename();

private:

	char *getField(char *str, int numberOfField, char sep);

	char *_filename;
	char *_creation_date;
	int _size;
};