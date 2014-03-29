/**************************************************************************
Michael Borsellino
---------------------------------------------------------------------
Project Description:
This program is an exercise in data parsing. 
Input: Any text file via redirect
Output: A list of the top ten characters/words/numbers in the file
        ranked by frequency
----------------------------------------------------------------------
Specific requirements:
-Character frequency ties broken by alphabetical order
-Word/Number frequency ties broken by order seen
-Word is defined as any series of characters broken by non-alpha
characters or whitespace.
-Number is defined as any series of number characters broken by
non-number characters or whitespace.
-words are case insensitive
-numbers with different appearence have different values. i.e. 001 != 1
***************************************************************************/
#include<iostream>
#include<map>
#include<unordered_map>
#include<utility>
#include<vector>
#include<iomanip>
#include<cctype>
#include<string>
using namespace std;

void Charcounter(vector<char>);
void Wordcounter(vector<char>, int);
//void Numbcounter(vector<char>);
int main()
{
  char readChar;
  vector<char> charRecord;

  //input process
  while(cin.peek() != char_traits<char>::eof())
  {
    cin.get(readChar);
    charRecord.push_back(readChar);
  }
  Charcounter(charRecord);
  Wordcounter(charRecord, 0);
  Wordcounter(charRecord,1);
}

void Charcounter(vector<char> baseVector)
{
  map<char, int> baseMap;
  vector<char> charvect;
  vector<int> intvect;
//**********
  //Placing characters into a map to easily maintain associations
  for(unsigned int i = 0; i < baseVector.size(); ++i)
  {
    ++baseMap[baseVector[i]];
  }
  //separating characters for future sorting while maintaining association order
  for(auto itr = baseMap.begin(); itr != baseMap.end(); ++itr)
  {
    charvect.push_back(itr->first);
    intvect.push_back(itr->second);
  }
//***********
  //Sorting sequence. Checks for frequency differences, and if that fails, alpha-ordering to sort
  for(unsigned int i = 0; i < charvect.size(); ++i)
  {
    for(unsigned int t = i + 1; t < charvect.size(); ++t)
    {
      if(intvect[t] > intvect[i])
      {
        swap(intvect[t],intvect[i]);
        swap(charvect[t],charvect[i]);
      }
      //checks the priority of ascii variables in list where occurance rates are the same
      else if(intvect[t] == intvect[i])
      {
        if(charvect[t] < charvect[i])
        {
          swap(charvect[t],charvect[i]);
        }
      }
    }//little step end
  }//big step end

//**********
  //output sequence    
  cout<<"Total "<<baseMap.size()<<" different characters, 10 most used:\n";
  for(unsigned int i = 0; i < charvect.size(); ++i)
  {
    if( i <= 9)
    {
      cout<<"No. "<<i<<": ";
      if(charvect[i] == '\t')
        cout<<"\\t";
      else if(charvect[i] == '\n')
        cout<<"\\n";
      else
        cout<<charvect[i];
      cout<<setw(20)<<intvect[i]<<endl;
    }
  }
}

//This function takes in the variable choice to decide whether it is looking for
//words or integers
void Wordcounter(vector<char> baseVector, int choice)
{
  unordered_map<string, int> baseMap;
  vector<string> stringTracker;
  vector<string> charvect;
  vector<int> intvect;
  auto ithead = baseVector.begin();

//converts all characters to lowercase
  for(unsigned int i = 0; i < baseVector.size(); ++i)
    baseVector[i] = tolower(baseVector[i]);

//********word mapping sequence-Checks for space/non-alpha character seporated words and
//pushes these strings onto a vector.
  if(choice == 0)
  {
  //initializes string vector from character vector and inserts into map
    for(auto ittail = baseVector.begin(); ittail != baseVector.end(); ++ittail)
    {
      if(!(isalpha(*ithead)))
      {
        ++ithead;
        ittail = ithead;
      }
      else if(!(isalpha(*ittail)))
      {
        string tempstring(ithead,ittail);
        stringTracker.push_back(tempstring);
        ithead = ittail;
      }
    }
  }
//********number mapping sequence-Checks for space/non-numerical character separated numbers
  //and pushes these strings onto a vector
  else
  {
  //initializes string vector from character vector 
    for(auto ittail = baseVector.begin(); ittail != baseVector.end(); ++ittail)
    {
      if(!(isdigit(*ithead)))
      {
        ++ithead;
        ittail = ithead;
      }
      else if(!(isdigit(*ittail)))
      {
        string tempstring(ithead,ittail);
        stringTracker.push_back(tempstring);
        ithead = ittail;
      }
    }
  }
//**********Sorting sequence  
  //inserts each string into the map for counting purposes to maintain 
  //associations and to keep priority
  vector<int> priorityTracker;
  for(unsigned int i = 0; i < stringTracker.size(); ++i)
  {
    ++baseMap[stringTracker[i]];
    if(baseMap[stringTracker[i]] == 1)
     priorityTracker.push_back(i);
  }

  //this splits the map up for sorting purposes
  for(auto itr = baseMap.begin(); itr != baseMap.end(); ++itr)
  {
    charvect.push_back(itr->first);
    intvect.push_back(itr->second);
  }

  //begins the sort
  for(unsigned int i = 0; i < charvect.size(); ++i)
  {
    for(unsigned int t = i + 1; t < charvect.size(); ++t)
    {
      if(intvect[t] > intvect[i])
      {
        swap(intvect[t],intvect[i]);
        swap(charvect[t],charvect[i]);
      }
      //checks for priority in list between elements with the same occurence rate
      else if(intvect[t] == intvect[i])
      {
        if(priorityTracker[t] > priorityTracker[i])
        {
          swap(charvect[i],charvect[t]);
          swap(priorityTracker[t], priorityTracker[i]);
           
        }
      }
    }//little step end
  }//big step end

//*******
  //output sequence
  cout<<"Total "<<baseMap.size()<<" different words, 10 most used:\n";
  for(unsigned int i = 0; i < charvect.size(); ++i)
  {
    if(i <= 9)
    {
      cout<<"No. "<<i<<": ";
      cout<<charvect[i];
      cout<<setw(20)<<intvect[i]<<endl;
    }
  }
}

