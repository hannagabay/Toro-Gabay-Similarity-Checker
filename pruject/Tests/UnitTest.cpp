#define CATCH_CONFIG_MAIN  
#include "Catch2.h"
#include <string>
using namespace std;

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
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


TEST_CASE( "Similarity score is produced", "[similarity score]" ) {
    REQUIRE( getSimilarity("test_program1.cpp", "test_program2.cpp") == 5.0/6.0*100 );
    REQUIRE( getSimilarity("test_program1.cpp", "test_program1.cpp") == 100.0 );
    REQUIRE( getSimilarity("test_program1.java", "test_program2.java") == 4.0/5.0*100 );
    REQUIRE( getSimilarity("test_program1.java", "test_program1.java") == 100.0 );
}
