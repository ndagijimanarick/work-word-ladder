#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <stack>
using namespace std;

 //this function will allow user to insert start and target words of same length
void searchWords(string &startword, string &targetword) {
  while (true) {
  	cout<<"Generation of word ladder:\n";
    cout << "Enter a start word: ";
    cin>>startword;   
    cout << "Enter target word: ";
    cin>>targetword;
    if (startword.length() == targetword.length()) {
      break;
    }
    cout << "/n!!! Please provide two words of the same length/n" << endl;
  }
}

void displayLadder(string startword, string targetword){
    queue<stack<string> > Q;
    stack<string> ladderword;
    stack<string> myStack;
    myStack.push(startword);
    Q.push(myStack);
    
    string readfile;
    ifstream wordscontainer("EnglishWords.dat");
    set<string> myEnglishWords;
    set<string> testedWords;
    
    if(wordscontainer.is_open()) {
      
	      while (wordscontainer >> readfile) {
	    	myEnglishWords.insert(readfile);
	      }  
	      
	      // when the queue is not empty:
	      while (!(Q.empty())) {
			stack<string> ladder = Q.front();
			Q.pop();
			string word = ladder.top();
			if (word == targetword) {
			  cout << "\n the shortest ladder from '" << startword << "' to '" << targetword << "'is: \n";
			  while(!ladder.empty()){
			  	ladderword.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!ladderword.empty()){
			  	cout<<" -> "<<ladderword.top();
			  	ladderword.pop();
			  }
			  cout<<"\n The ladder generated successfully!!! \n";
		} 
		else {
		//	test for a valid English word that differs if you change  one letter of the word on top of the stack implies to be
			  string tester;
			  for (int i = 0; i < word.size(); i++) {
			    for (char j = 'a'; j <= 'z'; j++) {
			    tester = word.substr(0, i) + j + word.substr(i + 1);

			    if (myEnglishWords.count(tester)) {
			      if (!testedWords.count(tester)) {
						stack<string> copy = ladder;
						copy.push(tester);
						Q.push(copy);
			      }
			    }
			    testedWords.insert(tester);
			}
		}
	      }
	    }
    } else {
      cout << "no ladder could be found." << endl;
    }    
}

int main() { 
  string startword, targetword;
  searchWords(startword, targetword); 
  displayLadder(startword, targetword);   
  return 0;
}
