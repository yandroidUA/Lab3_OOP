#include "CFile.h"

CFile::CFile() {
	_size = 0;
	_filename = NULL;
	_creation_date = NULL;
}

CFile::CFile(const CFile &file) {
	int fileNameSize = strlen(file._filename);
	int creationDateSize = strlen(file._creation_date);

	_size = file._size;

	_filename = new char[fileNameSize + 1];
	_creation_date = new char[creationDateSize + 1];

	for (int i = 0; i < fileNameSize; i++) {
		_filename[i] = file._filename[i];
	}

	for (int i = 0; i < creationDateSize; i++) {
		_creation_date[i] = file._creation_date[i];
	}

	_filename[fileNameSize] = '\0';
	_creation_date[creationDateSize] = '\0';
}

CFile::CFile(const char *filename,const char *creation_date, int size)
{
	if (filename == NULL || creation_date == NULL) {
		exit(1);
	}

	int fileNameSize = strlen(filename);
	int creationDateSize = strlen(creation_date);

	_size = size;

	_filename = new char[fileNameSize + 1];
	_creation_date = new char[creationDateSize + 1];

	for (int i = 0; i < fileNameSize; i++) {
		_filename[i] = filename[i];
	}

	for (int i = 0; i < creationDateSize; i++) {
		_creation_date[i] = creation_date[i];
	}

	_filename[fileNameSize] = '\0';
	_creation_date[creationDateSize] = '\0';
}

char * CFile::getField(char *str, int numberOfField, char sep) {
	int currentField = 0;
	int strSize = strlen(str);
	char *buffer = new char[50];
	int bufferIndex = 0;

	for (int i = 0; i < strSize; i++) {
		if (str[i] == sep) {
			currentField++;
			continue;
		}

		if (currentField == numberOfField) {
			buffer[bufferIndex] = str[i];
			bufferIndex++;
		}
	}

	buffer[bufferIndex] = '\0';
	return buffer;
}

void CFile::parseFrom(char *str){
	_filename = getField(str, 0, ';');
	_creation_date = getField(str, 1, ';');
	_size = atoi(getField(str, 2, ';'));
}

CFile& CFile::operator= (const CFile &file) {
	if ((*this)._filename == file._filename) {
		return *this;
	}

	delete[] _filename;
	delete[] _creation_date;

	int fileNameSize = strlen(file._filename);
	int creationDateSize = strlen(file._creation_date);

	_size = file._size;

	_filename = new char[fileNameSize + 1];
	_creation_date = new char[creationDateSize + 1];

	for (int i = 0; i < fileNameSize; i++) {
		_filename[i] = file._filename[i];
	}

	for (int i = 0; i < creationDateSize; i++) {
		_creation_date[i] = file._creation_date[i];
	}

	_filename[fileNameSize] = '\0';
	_creation_date[creationDateSize] = '\0';

	return *this;
}

CFile::~CFile()
{
	if (_filename != NULL) {
		delete[] _filename;
	}
	if (_creation_date != NULL) {
		delete[] _creation_date;
	}

	_filename = NULL;
	_creation_date = NULL;
	
}

void CFile::rename(const char* filename) {
	delete[] _filename;
	_filename = NULL;

	if (filename == NULL) {
		exit(1);
	}

	int fileNameSize = strlen(filename);
	_filename = new char[fileNameSize + 1];

	for (int i = 0; i < fileNameSize; i++) {
		_filename[i] = filename[i];
	}

	_filename[fileNameSize] = '\0';
}

bool CFile::isAfter(const char *time) {
	if (time == NULL || _filename == NULL || _creation_date == NULL) {
		return false;
	}

	int year = atoi(getField(const_cast<char*>(time), 2, '.'));
	int month = atoi(getField(const_cast<char*>(time), 1, '.'));
	int day = atoi(getField(const_cast<char*>(time), 0, '.'));

	int mYear = atoi(getField(_creation_date, 2, '.'));
	int mMonth = atoi(getField(_creation_date, 1, '.'));
	int mDay = atoi(getField(_creation_date, 0, '.'));

	if (mYear > year) {
		return true;
	}

	if (mYear < year) {
		return false;
	}

	if (mMonth > month) {
		return true;
	}

	if (mMonth < month) {
		return false;
	}

	if (mDay > day) {
		return true;
	}

	return false;
}

const char *CFile::getFilename() {
	return _filename;
}

bool CFile::operator!=(const CFile & file)
{
	if (_size != file._size || strcmp(_filename, file._filename) || strcmp(_creation_date, file._creation_date)) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& stream, CFile &obj) {
	stream << "Filename: " << obj._filename << " Creationdate: " << obj._creation_date << " size: " << obj._size << endl;
	return stream;
}