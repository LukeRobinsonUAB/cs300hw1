//g++ hw1.cpp -o hw1 -std=c++23
#include <string>
#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <random>
#include <unordered_set>
#include <time.h>

using namespace std;

string qwertyLeftOne(string str) {
    //edit string in place
    using namespace std;
    unordered_map<char, char> leftOne = {
        {'w', 'q'},
        {'e', 'w'},
        {'r', 'e'},
        {'t', 'r'},
        {'y', 't'},
        {'u', 'y'},
        {'i', 'u'},
        {'o', 'i'},
        {'p', 'o'},
        {'s', 'a'},
        {'d', 's'},
        {'f', 'd'},
        {'g', 'f'},
        {'h', 'g'},
        {'j', 'h'},
        {'k', 'j'},
        {'l', 'k'},
        {'x', 'z'}, 
        {'c', 'x'},
        {'v', 'c'},
        {'b', 'v'},
        {'n', 'b'},
        {'m', 'n'},
        {'1', '`'},
        {'2', '1'},
        {'3', '2'},
        {'4', '3'},
        {'5', '4'},
        {'6', '5'},
        {'7', '6'},
        {'8', '7'},
        {'9', '8'},
        {'0', '9'},
        {',', 'M'}, // ,converts to lowercase m only never upper? edit: i did't read instructions carefully so I made my code work for lower and upper
        {']', '['},
        {'}', '{'},
        {'.', ','},
        {'>', '<'},
        {'<', 'M'}, // not sure if supposed to do this? what do for '<' input? stay same? or change to 'M'
        {'/', '.'},
        {'\'',';'},
        {'"', ':'},
        {'\\', ']'},
        {'|', '}'},
        {'=', '-'},
        {'+', '_'},
        {':', 'L'},
        {'!', '~'},
        {'@', '!'},
        {'#', '@'},
        {'$', '#'},
        {'%','$'},
        {'^','%'},
        {'&', '^'},
        {'*', '&'},
        {'(', '*'},
        {')', '('},
        {'-', '0'},
        {'_', ')'},
    };

    for (int i = 0; i < str.length(); i++) {
        bool UPPER_FLAG = false;           //init uppercase flag for this iter of loop
        UPPER_FLAG = isupper(str[i]);      //set flag
        if (UPPER_FLAG) {
            str[i] += 32;                  //now lowercase if not already
        }
        if (leftOne.contains(str[i])) {    //MUST USE C++ std 20 or higher!!!!! for contains method. Check your c_cpp_properties.json if error 135
            str[i] = leftOne.at(str[i]);
            if (UPPER_FLAG) {
                str[i] -= 32;              //convert back to uppercase if flag set true             
            }                              //would give extraneous results if 'Q', 'A', 'Z' allowed in input, could use tolower
        }                                  
        //dont change char if no key for it :)
    }
    return str;
}

//must define above SearchBySubject so the paramter type is already defined
struct libraryT {
    string title;
    std::vector<string> authors;
    int catalogNum;
    std::vector<string> subjectHeadings;
    string publisher;
    int yearPublished;
    bool bCirculating;
};

//passing by "const ref" makes sure we dont edit our library because its a const and its more efficent to pass large things as ref such as a 1,000 long vector of unknown size
void SearchBySubject(const std::vector<libraryT>& vec, const string& subject) {
    for (const libraryT& s : vec){
        for (const string& str : s.subjectHeadings) {
            if (!str.compare(subject)) {
                cout << "Title: " << s.title << endl << "Author: " << s.authors.at(0) << endl << "LCCN: " << s.catalogNum << endl;
                //break? perhaps we need a break incase a book has non-unique subject headings so entries are not repeated? 
            }
        }
    }
}

void hangman() {
    //open file
    ifstream hangmanWordFile;
    hangmanWordFile.open("hangman.txt"); //error handle
    
    //get num of lines in hangman.txt // this will actually count ALL whitespace char and may count EOF once or twice.
    int numLines = 0;
    string temp;
    if (hangmanWordFile.is_open()){
        while (hangmanWordFile.good()) {
            hangmanWordFile >> temp;
            numLines++;                         
        }
    }
    hangmanWordFile.close();

    //pick random word
    //perhaps let user select difficulty or category
    srand(time(0));
    int lineOfWord = rand() % numLines;
    string word;
    hangmanWordFile.open("hangman.txt");
    if (hangmanWordFile.is_open()) {
        int i = 0;
        while (hangmanWordFile.good() && (i < lineOfWord)) {
            getline(hangmanWordFile, word);
            i++;
        }
    }
    else {
        cout << "ERROR file moved/deleted? press enter to close" << endl;
        cin.ignore();
        exit(-1);
    }
    hangmanWordFile.close();
    cout << "(don't show to user) word selected: " << word << endl; //debug line

    unordered_set<char> incorrectGuesses;   //maybe use map for order so we display in same order to user always
    unordered_set<char> correctGuesses;
    correctGuesses.emplace('\0');
    int incorrectGuessesAllowed = 10;       //change this for difficulty
    int incorrectGuessesNum = 0;           //always init 0
    bool notGuessed = true;
    while (notGuessed && (incorrectGuessesNum < incorrectGuessesAllowed)) {
        //system("clear");
        for (int f = 0; f < word.length(); f++) {

        //}
        //for (char c : word) {
            if (correctGuesses.contains(word[f])) {
                cout << " " << word[f] << "";
            }
            else {
                if (f < word.length()-1)
                    cout << " _ ";
            }
        }
        cout << " \t incorrect guesses amount = " << incorrectGuessesNum << "     already guessed letters: ";
        for (char c : incorrectGuesses) {
            cout << " " << c;
        }
        cout << endl;

        char guess;
        cin >> guess;
        if (word.contains(guess)) {
            correctGuesses.emplace(guess);
        }
        else {
            incorrectGuesses.emplace(guess);
            incorrectGuessesNum++;
        }
        
        //check if player has won the game!
        int j = 1;
        int r = 0;
        for (r = 0; r < word.length(); ++r) {
            if (correctGuesses.contains(word[r]))
                j++;
        }

        if (r == j) {
            notGuessed = false; // player won! all char in word appear in set of correctGuesses
        }

    }
    if (notGuessed)
        cout << "you lost! The hangman was hanged :/" << endl;
    else
        cout << "you won! The hangman was spared :)" << endl;
    cout << "The word was " << word << endl;


}

int main() {

    //problem 1
    string inputProblemOne = "O S, GOMR YPFSU/";
    string outputProblemOne = qwertyLeftOne(inputProblemOne);
    cout << outputProblemOne << endl;

    //problem 4
    //libraryT libdata; //default values
    //5 sample books
    libraryT Book1 {"title", {"author1", "author2", "author3"}, 0, {"subject1", "subject2"}, "publisher", 1999, false};
    libraryT Book2 {"art book", {"Pablo Picasso", "Bob Ross", "paul signac"}, 1, {"art", "pointillism", "impressionism", "painting", "abstract"}, "Art Publishing, INC", 2003, true};
    libraryT Book3 {"The C++ Programming Language, 4th Edition", {"Bjarne Stroustrup"}, 2, {"programming", "c++", "code", "coding", "c"}, "Addison-Wesley Professional", 2023, true};
    libraryT Book4 {"The Hobbit", {"John Ronald Reuel Tolkien", "J.R.R. Tolkien"}, 3, {"fiction", "quest", "magic"}, "George Allen & Unwin", 1937, true};
    libraryT Book5 {"Programming Language Foundations", {"Aaron Stump", "Beth Lang Golub", "Joseph Romano"}, 4, {"lambda calculus", "functional programming", "type theory", "determinism", "Partial correctness assertions"}, "Don Fowley", 2014, true};
    std::vector<libraryT> libdatabaseVec({Book1, Book2, Book3, Book4, Book5}); //vector of structs
    SearchBySubject(libdatabaseVec, "type theory");

    //problem 5
    hangman();




    return EXIT_SUCCESS;
}