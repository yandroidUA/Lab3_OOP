#include <iostream>
#include "Iterator.h"
#include "List.h"
#include "CFile.h"
using namespace std;

List<CFile> existingFiles;
List<CFile> deletedFiles;

void addFile(const char *filename, const char *time, int size);
void deleteFile(const char *filename);
void restore(const char *filename);
void deleteBefore(const char *time);
void renameFile(const char *oldName, const char *newName);

int main() {
	
	existingFiles.load("test.csv");
	const char *time = "27.01.2019";

	cout << "\t\tEXISTING FILES" << endl;
	existingFiles.Print();

	const char *filename = "testAdding";
	const char *mBirth = "12.08.2000";
	int size = 51984;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "Adding file with name: " << filename << " time: " << mBirth << " size: " << size << endl;
	addFile(filename, mBirth, size);

	cout << "\t\tAFTER ADDING" << endl;
	existingFiles.Print();

	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "DELETING ALL FILES BEFORE " << time << endl;
	deleteBefore(time);

	cout << "\t\tAFTER DELETING" << endl;
	existingFiles.Print();
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "DELETING FILE WITH NAME dima.cpp" << endl;
	deleteFile("dima.cpp");

	cout << "\t\tAFTER DELETING" << endl;
	existingFiles.Print();
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "RESTORE FILE WITH NAME dima.cpp" << endl;
	restore("dima.cpp");

	cout << "\t\tAFTER RESTORE" << endl;
	existingFiles.Print();

	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\tRENAMING FILE WITH NAME dima.cpp to renameTest" << endl;
	renameFile("dima.cpp", "renameTest");

	existingFiles.Print();
	
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "PRINTING DELETED LIST FILES" << endl;
	deletedFiles.Print();

	system("pause");
	return(0);
}

void addFile(const char *filename, const char *time, int size) {
	CFile newFile(filename, time, size);
	existingFiles.push_front(newFile);
}

void deleteFile(const char *filename) {
	List<CFile>::iterator it = existingFiles.begin();
	List<CFile>::iterator itNext;

	while (it != existingFiles.end()) {
		if (!strcmp((*it).data.getFilename(), filename)) {
			itNext = (*it).next;
			existingFiles.splice(it, deletedFiles);
			it = itNext;
		} else {
			it++;
		}
	}
}

void restore(const char *filename) {

	List<CFile>::iterator it = deletedFiles.begin();
	List<CFile>::iterator itNext;

	while (it != deletedFiles.end()) {
		if (!strcmp((*it).data.getFilename(), filename)) {
			itNext = (*it).next;
			deletedFiles.splice(it, existingFiles);
			it = itNext;
		}
		else {
			it++;
		}
	}
}

void deleteBefore(const char *time) {
	List<CFile>::iterator it = existingFiles.begin();
	List<CFile>::iterator itNext;

	while (it != existingFiles.end()) {
		if (!(*it).data.isAfter(time)) {
			itNext = (*it).next;
			existingFiles.splice(it, deletedFiles);
			it = itNext;
		} else {
			it++;
		}
	}
}

void renameFile(const char *oldName, const char *newName) {
	for (List<CFile>::iterator it = existingFiles.begin(); it != existingFiles.end(); it++) {
		if (!strcmp((*it).data.getFilename(), oldName)) {
			(*it).data.rename(newName);
		}
	}
}