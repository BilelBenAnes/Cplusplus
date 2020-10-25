#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "map"
#include <vector>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;
struct DateTime
{
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int millisec;

  DateTime()
  {
  }
  DateTime(string date, string time)
  {
    getData(date, time);
  }

  void getData(string date, string time)
  {
    year = stoi(getData(date, '-'));
    month = stoi(getData(date, '-'));
    day = stoi(date);
    hour = stoi(getData(time, '-'));
    min = stoi(getData(time, '-'));
    sec = stoi(getData(time, '-'));
    millisec = stoi(time);
  }
  string getData(string &input, char delimiter)
  {
    string output = input.substr(0, input.find(delimiter));
    input.erase(0, input.find(output) + output.length() + 1);
    return output;
  }

  string toString()
  {
    return " (" + to_string(day) + "-" + to_string(month) + "-" + to_string(year) + "-" + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec) + "):";
  }
};
struct AtcoCommand
{
  string fileName;
  string wordSequence;
  string commands[6];
  string mainCommands[6];
  string date;
  string time;
  DateTime formattedDateTime;
  AtcoCommand()
  {
  }
  AtcoCommand(string fileNameInput, string wordSequenceInput, string commandsInput)
  {
    getDateTime(fileNameInput);
    formattedDateTime = DateTime(date, time);
    fileName += date + "__" + time + formattedDateTime.toString();
    wordSequence = wordSequenceInput;
    getCommands(commandsInput);
  }

  void getCommands(string &commandsInput)
  {
    int index = 0;
    istringstream f(commandsInput);
    string line;
    while (getline(f, line))
    {
      commands[index++] = line;
      if (line.length() > 5)
      {
        mainCommands[index++] = getMainCommand(line);
      }

      cout << commands[index] << endl;
    }
  }
  string getMainCommand(string input)
  {
    while (input.find(" ") != -1)
    {
      if (input.at(input.find(" ") + 1) != ' ')
      {
        break;
      }
      input = input.erase(0, input.find(" ") + 1);
    }
    input = input.erase(0, input.find(" ") + 1);
    string output = input.substr(0, input.find(" "));
    input = input.erase(0, input.find(" ") + 1);
    output = input.substr(0, input.find(" "));
    return output;
  }
  void getDateTime(string input)
  {
    date = input.substr(0, input.find("__"));
    time = input.substr(input.find("__") + 2, input.length()).substr(0, input.substr(input.find("__") + 2, input.length()).find(":"));
  }
  string toString()
  {
    string output = fileName + " \n" + wordSequence + " :\n", command = "";
    for (int i = 0; i < 6; i++)
    {
      if (commands[i].length() > 10)
      {
        command += commands[i] + ";";
      } //+ mainCommands[i] + ";";
    }
    output += command;

    return output;
  }
};
void wordsCount(const string &str, map<string, int> &wordsMap)
{
  int count = 1;
  istringstream wordStream(str);
  string word;
  while (wordStream >> word)
  {
    pair<map<string, int>::iterator, bool> returnValue;
    returnValue = wordsMap.insert(pair<string, int>(word, count));
    if (returnValue.second == false)
    {
      ++returnValue.first->second;
    }
  }
};
bool cmp(pair<string, int> &a,
         pair<string, int> &b)
{
  return a.second > b.second;
};

void sortWords(map<string, int> &M)
{
  vector<pair<string, int>> A;
  int sizeB = 0;
  for (auto &it : M)
  {
    A.push_back(it);
  }
  sort(A.begin(), A.end(), cmp);
  //Get Top 10 occured
  if (A.size() > 10)
  {
    sizeB = 10;
  }
  else
  {
    sizeB = A.size();
  }
  vector<pair<string, int>> B(A.begin(), A.begin() + sizeB);
  //print
  cout
      << "The top 10 occurences" << endl;
  int counter = 1;
  for (auto &it : B)
  {
    if (counter < 4)
    {
      cout << counter << ".";
      for (size_t i = 0; i < 20 - it.first.length(); i++)
      {
        cout << " ";
      }
      cout << it.first << ":   "
           << it.second << endl;
      counter++;
    }
    else
    {
      for (size_t i = 0; i < 22 - it.first.length(); i++)
      {
        cout << " ";
      }
      cout << it.first << ":   "
           << it.second << endl;
    }
  }
};
void sortCommands(map<string, int> &M)
{
  vector<pair<string, int>> A;
  int sizeB = 0;
  for (auto &it : M)
  {
    A.push_back(it);
  }
  sort(A.begin(), A.end(), cmp);
  //Get Top 10 occured
  if (A.size() > 10)
  {
    sizeB = 10;
  }
  else
  {
    sizeB = A.size();
  }
  vector<pair<string, int>> B(A.begin(), A.begin() + sizeB);
  //print
  cout
      << "The top 20 type occurences specified in longText.txt" << endl;
  int counter = 1;
  for (auto &it : B)
  {
    if (counter < 2)
    {
      cout << counter << ".";
      for (size_t i = 0; i < 20 - it.first.length(); i++)
      {
        cout << " ";
      }
      cout << it.first << ":   "
           << it.second << endl;
      counter++;
    }
    else
    {
      for (size_t i = 0; i < 22 - it.first.length(); i++)
      {
        cout << " ";
      }
      cout << it.first << ":   "
           << it.second << endl;
    }
  }
};
int main()
{
  map<string, int> wordsMap;
  map<string, int> commandsMap;
  AtcoCommand atcoCommands[1000];
  int index = 0;
  string line, fileName, wordSequence, commands;
  ifstream file("longTest.txt");
  if (file.is_open())
  {
    while (file.good())
    {
      getline(file, line);
      if (line.find(":") != -1)
      {
        if (wordSequence.length() != 0)
        {
          AtcoCommand atcoCommand = AtcoCommand(fileName, wordSequence, commands);
          atcoCommands[index++] = atcoCommand;
          commands = "";
        }
        fileName = line;
        getline(file, line);
        wordSequence = line;
      }
      else
      {
        commands += line + "\n ";
      }
    }
  }
  AtcoCommand atcoCommand = AtcoCommand(fileName, wordSequence, commands);
  atcoCommands[index++] = atcoCommand;
  file.close();
  for (size_t i = 0; i < 15; i++)
  {
    if (atcoCommands[i].toString().length() > 8)
    {
     cout << atcoCommands[i].toString() << endl;
    }
    
    wordsCount(atcoCommands[i].wordSequence, wordsMap);
    for (size_t k = 0; k < 6; k++)
    {
      wordsCount(atcoCommands[i].mainCommands[k], commandsMap);
    }
  }
  sortWords(wordsMap);
  sortCommands(commandsMap);
  return 0;
}