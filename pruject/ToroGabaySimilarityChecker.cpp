#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <Windows.h>
#include <vector>

using namespace std;

vector<string> get_all_files_names_within_folder(string folder)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) { 
        do { 
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return names;
}

double getSimilarity(string fileName1, string fileName2) {
	double similar = 0, total = 0;
	string line1, line2, temp;
	int length1, length2;
	
	ifstream file1;
	file1.open (fileName1.c_str(), ios::binary );
	file1.seekg (0, ios::end);
	length1 = file1.tellg();
	file1.close();
	

	ifstream file2;
	file2.open (fileName2.c_str(), ios::binary );
	file2.seekg (0, ios::end);
	length2 = file2.tellg();
	file2.close();
	
	if (length2 > length1) {
		temp = fileName1;
		fileName1 = fileName2;
		fileName2 = temp;
	}
	
	file1.open(fileName1);
	
	while ( getline(file1, line1) ) {
		if (line1.find_first_not_of(' ') == std::string::npos) continue;
		file2.open(fileName2);
		while ( getline(file2, line2) ) {
			if (strcmp(line1.c_str(), line2.c_str()) == 0) {
				similar += 1.0;
				break;
			}
		}	
		file2.close();
		
		total += 1.0;
	}
	file1.close();
	
	
	return similar/total*100;
}

int main() {
	vector<string> fileNamesV = get_all_files_names_within_folder("Submissions");
	
	string* fileNames = &fileNamesV[0];
	
	double SimilarityScores[35][35];
	int x, y;
	
	for (y = 0; y < 35; y++) {
		for (x = 0; x < 35; x++) {
			SimilarityScores[x][y] = getSimilarity("Submissions/" + fileNames[y], "Submissions/" + fileNames[x]);
		}
	}
	
	for (y = 0; y < 35; y++) {
		for (x = 0; x < 35; x++) {
			cout << fixed;
    		cout << setprecision(1);
			cout << SimilarityScores[x][y] << "\t";
		}
		cout << "\n";
	}
}


