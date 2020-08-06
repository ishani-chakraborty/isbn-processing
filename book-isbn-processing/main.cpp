#include <iostream>
#include <vector>
/* Ishani Chakraborty
Final Part B
This program prompts the user to enter the 
first 9 digits of an ISBN code and displays
the complete 10- digit ISBN code including all 0
*/
using namespace std;

bool validateIsbn(char isbn[]);
char calculate10thChar(char isbn[]);
string formatWithHyphen(string isbnStr, char lastChar);

bool validateIsbn(char isbn[]) {
    int i = 0;
    while(isbn[i] != '\0') {
        if(isbn[i] >= '0' && isbn[i] <= '9') {
            ++i;
        } else {
            return false;
        }
    }
    return (i == 9);
}

char calculate10thChar(char isbn[]) {
    int sum = 0;
    int i = 0;
    while(isbn[i] != '\0') { //remember this is a null-terminated character array (technically be the last index)
        int digit = isbn[i]-'0';
        ++i;
        sum += (digit * i);
    }
    sum %= 11;
    if(sum != 10) {
       return (char)(sum + 48); //look at ASCII chart to calculate
    }
    return 'X';
}

string formatWithHyphen(string isbnStr, char lastChar)
{
    /*inserts hyphens at respective indicies 
    once char array is converted to string*/
    isbnStr.insert(1,"-");
    isbnStr.insert(5,"-");
    isbnStr.insert(11,"-");

    isbnStr.insert(isbnStr.length(), string(1, lastChar));
    return isbnStr;
}

int main()
{
    vector<string> validInput;
    vector<char> checkedSum;

    const int SIZE = 30;
    char isbn[SIZE];

    cout << "This program calculates the lastChar of a 9-digit ISBN code and displays the 10-digit ISBN." << endl;
    cout << "Enter the 9 digits for the ISBN code: ";
    cin.getline(isbn, SIZE);
   
    while (isbn[0] != '\0') { //sentinel loop 
        bool isValid = validateIsbn(isbn);
        if (!isValid) {
            cout << "\nThe input ISBN code is not valid.\n";
        } else {
            char lastChar = calculate10thChar(isbn);
            string isbn9Str(isbn); // convert char array to string
            cout << "\nThe 10-digit ISBN code is " << isbn9Str << lastChar << endl;
            cout << "The hyphenated ISBN code is " << formatWithHyphen(isbn9Str, lastChar) << endl;
            validInput.push_back(isbn9Str);
            checkedSum.push_back(lastChar);
        }
        cout << "\nEnter the 9 digits for the ISBN code or press Enter to exit: ";
        cin.getline(isbn, SIZE);
    }
    cout << "\nSummary Report\n";
    cout << "ISBN         Checksum\n\n";
    
    for (int i = 0; i < validInput.size(); i++) {
        cout << validInput[i] << "    " << checkedSum[i] << "\n";
    }
    return 0;
}