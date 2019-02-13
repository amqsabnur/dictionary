/***
Fardous Sabnur
Prof: Maryash
135/136
project 2
Add, replace, remove, find identical phoneme
th
This C++ project is going to implement a linguistic application that uses a pronunciation dictionary 
for finding words with similar pronunciation.
It reads the file cmudict.0.7a.txt 
phase 1) User enters a word, and the program only reports pronunciation as a list of phonemes. 
phase 2) User enters a word — the program reports pronunciation as a list of phonemes AND 
   		a list of words that sound the same (is made up of exactly the same sequence of phonemes). 
phase 3)In addition to the functionality of phases I and II,
		print a list of words that can be obtained by replacing just one phoneme 
		words made up of exactly the same sequence of phonemes with just one of them different. 
Phase 4) In addition to the functionality of phases I, II and III, 
		print a list of words that can be obtained by adding just one phoneme — 
		words made up of exactly the same sequence of phonemes with just one additional one 
		anywhere in the original sequence of phonemes.
Phase 5) In addition to the functionality of phases I, II and III, IV
		
***/
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
using namespace std;

void splitOnSpace(string s, string& before, string& after);   // splits the first word by the 1st space
string convert(string word);    // coverts all the user input words to uppercase;
string pronPhonemes(string upWord);             // pronounciation of the word with all the phonemes
int countPhonemes(string phonemes);                           // counts the number of phonemes
string findIdentical(string phonemes, string upWord);           //finds other words with identical phonemes
string replacePhoneme(string phonemes, string afterSpace, string word);  // replaces a part of the phoneme and checks if there's another word with the similar phoneme
string removePhoneme(string phonemes, string afterSpace, string word);   // removes one part of the phoneme and checks if there's another word with the similar phoneme
string addPhoneme(string phonemes, string afterSpace, string word);      // adds a part to the phoneme and checks if there's another word with the similar phoneme
void decide(int count, string phonemes, string upWord);       // decides whether to add, remove, or replace
void splitPhonemes(string line, string array[], int& size);   // splits each parts of the phoneme

int main() 
{
  string word;
  cin >> word;
  string upWord = convert(word);
  string phonemes = pronPhonemes(upWord);
  if (phonemes == "") 
  {
    return 0;            // if the phoneme doesn't exist, exit;
  }
  string identical = findIdentical(phonemes, upWord);
  int count = countPhonemes(phonemes);
  decide(count, phonemes, upWord);
}
void splitOnSpace(string s, string& before, string& after) // splits the first word by the 1st space 
{  
  before = "";
  after = "";
  int i = 0;
  while (i < s.size() && not isspace(s[i]))
   {
    before += s[i];
    i++;
  }  
  i++;
  while (i < s.size()) 
  {
    after += s[i];
    i++;
  }
}
string convert(string word)    // makes them case-insensitive, can't just use "to uppercase) because that'll include numbers
{
  char letter;
  string upWord= "";
  for (int i = 0; i < word.length(); i++) {
    letter = word[i];
    if ((int)letter == 39) {
      upWord += letter;
    } else if (isupper(letter)) {
      upWord += letter;
    } else if (islower(letter)) {
      letter = char((int)letter - 32);
      upWord += letter;
    } else {
      return "";
    }
  }
  return upWord;
}
string pronPhonemes(string upWord)  //returns all the words after the first space
{
  bool found = false;
  string word;
  string phonemes;
  string beforeSpace;
  string afterSpace;
  ifstream library;
  library.open("cmudict.0.7a");
  while (library >> word) 
  {
    if (word == upWord) 
	{
      found = true;
      getline(library, phonemes);
      splitOnSpace(phonemes, beforeSpace, afterSpace);
      splitOnSpace(afterSpace, beforeSpace, afterSpace);
      cout << "Pronounciation: " << afterSpace << endl;
      cout << "" << endl;
      break;
    }
  }
  if (!found) 
  {
    cout << "Not found" << endl;
    return "";
  }
  return afterSpace;
}
int countPhonemes(string phonemes) 
{
  int count = 1;
  for (int i = 0; i < phonemes.length(); i++)
   {
    if (isspace(phonemes[i])) 
	{
      count++;
    }
  }
  return count;
}
string findIdentical(string phonemes, string upWord)  //finds other words with same phoneme
{
  bool found = false;
  string word;
  string newPhonemes;
  string beforeSpace;
  string afterSpace;
  string identical;
  string allIdentical;
  ifstream library;

  library.open("cmudict.0.7a");
  while (library >> word) 
  {
    getline(library, newPhonemes);
    splitOnSpace(newPhonemes, beforeSpace, afterSpace);
    splitOnSpace(afterSpace, beforeSpace, afterSpace);
    if (word == upWord) 
	{
      found = false;
    } else if (afterSpace == phonemes) 
	{
      found = true;
      string identical = convert(word);
      allIdentical += " ";
      allIdentical += identical;
    }
  }
  cout << "Identical: " << allIdentical << endl;
  if (!found) 
  {
    identical = "";
  }
  return identical;
}
string replacePhoneme(string phonemes, string afterSpace, string word) {    //replaces phonemes with other words
  int sizePho = 0;
  int sizeAft = 0;
  int strike = 0;
  string replaced;
  string oldPhonemes[20];
  string newPhonemes[20];
  splitPhonemes(phonemes, oldPhonemes, sizePho);
  splitPhonemes(afterSpace, newPhonemes, sizeAft);
  for (int i = 0; i < sizePho; i++) 
  {
    if (oldPhonemes[i] != newPhonemes[i]) 
	{
      strike++;
    }
  }
  if (strike != 1) 
  {
    return "";
  } 
  else
   {
    if (word == "")
	 {
      return "";
    } 
	else 
	{
      word += " ";
      return word;
    }
  }
}
string addPhoneme(string phonemes, string afterSpace, string word) // adds a part to the phoneme and checks if there's another word with the similar phoneme
{
  bool strike = false;
  int sizePho = 0;
  int sizeAft = 0;
  int counter = 0;
  string added;
  string oldPhonemes[20];
  string newPhonemes[20];
  splitPhonemes(phonemes, oldPhonemes, sizePho);
  splitPhonemes(afterSpace, newPhonemes, sizeAft);
  for (int i = 0; i < sizeAft; i++) 
  {
    if (oldPhonemes[i] != newPhonemes[counter]) 
	{
      if (!strike) 
	  {
        strike = true;
        counter++;
        if (oldPhonemes[i] != newPhonemes[counter]) 
		{
          return "";
        }
      } 
	  else 
	  {
        return "";
      }
    }
    counter++;
  }
  word += " ";
  return word;
}
string removePhoneme(string phonemes, string afterSpace, string word) {
  return addPhoneme(afterSpace, phonemes, word);
}



void decide(int count, string phonemes, string upWord) // decides whether to add, remove, or replace
{
  bool done = false;
  string beforeSpace;
  string afterSpace;
  string newPhonemes;
  string word;
  ifstream library;
  string replaced, removed, added;
  library.open("cmudict.0.7a");
  while (!done && library >> word) 
  {
    string newWord = convert(word);
    getline(library, newPhonemes);
    splitOnSpace(newPhonemes, beforeSpace, afterSpace);
    splitOnSpace(afterSpace, beforeSpace, afterSpace);
    int x = countPhonemes(afterSpace);
    if (x == count && newWord != upWord) 
	{
      replaced += replacePhoneme(phonemes, afterSpace, newWord);
    } 
	else if (x == count - 1) 
	{
      removed += removePhoneme(phonemes, afterSpace, newWord);
    } 
	else if (x == count + 1) 
	{
      added += addPhoneme(phonemes, afterSpace, newWord);
    } 
	else 
	{
      done = false;
    }
  }
  cout << "Add phoneme: " << added << endl;
  cout << "Remove phoneme: " << removed << endl;
  cout << "Replace phoneme: " << replaced << endl;
}
void splitPhonemes(string line, string array[], int& size)  // splits each parts of the phoneme
{
  string temp;
  for (int i = 0; i < line.length(); i++) 
  { 
    if (line[i] == ' ' && temp != "") 
	{
      array[size] = temp;
      temp = "";
      size++;
    } 
	else 
	{
      temp += line[i];
    }
  }
  if (temp != "")
  {
    array[size] = temp;
    size++;
  }
}

