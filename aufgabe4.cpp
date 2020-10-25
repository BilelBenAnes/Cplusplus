#include <ostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "map"
#include <vector>
#include <bits/stdc++.h>
#include <iterator>
#include <algorithm>

using namespace std;
/*Struct Datetime
---------------------------*/
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

/*Struct AtoCommand
---------------------------*/
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

  void getCommands(string commandsInput)
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
      }
    }
    output += command;

    return output;
  }
};
/*Method to use
---------------------------*/
string readTextFile(string url)
{
  string output, line;
  ifstream myfile(url);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      output += line + "\n";
    }
    myfile.close();
  }
  else
    cout << "Unable to open file";
  return output;
}

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
  return a.second != b.second ? a.second > b.second : a.first > b.first;
};

string topWords(map<string, int> &M)
{
  string output = "";
  vector<pair<string, int>> A;
  int sizeB = 0;
  for (auto &it : M)
  {
    A.push_back(it);
  }
  sort(A.begin(), A.end(), cmp);
  if (A.size() > 10)
  {
    sizeB = 10;
  }
  else
  {
    sizeB = A.size();
  }
  vector<pair<string, int>> B(A.begin(), A.begin() + sizeB);
  output += "The top 10 occurences\n";
  int counter = 1;
  for (auto &it : B)
  {
    if (counter < 4)
    {
      output += "" + to_string(counter) + ".";
      for (size_t i = 0; i < 20 - it.first.length(); i++)
      {
        output += " ";
      }
      output += it.first + ":   " + to_string(it.second) + "\n";
      counter++;
    }
    else
    {
      for (size_t i = 0; i < 22 - it.first.length(); i++)
      {
        output += " ";
      }
      output += it.first + ":   " + to_string(it.second) + "\n";
    }
  }
  return output;
};

string topCommands(map<string, int> &M, int amount, string url)
{
  string output = "";
  vector<pair<string, int>> A;
  int sizeB = 0;
  for (auto &it : M)
  {
    A.push_back(it);
  }
  sort(A.begin(), A.end(), cmp);
  if (A.size() > amount)
  {
    sizeB = amount;
  }
  else
  {
    sizeB = A.size();
  }
  vector<pair<string, int>> B(A.begin(), A.begin() + sizeB);
  output += "The top" + to_string(amount) + " type occurences specified in " + url + "\n";
  int counter = 1;
  for (auto &it : B)
  {
    if (counter < 2)
    {
      output += "" + to_string(counter) + ".";
      for (size_t i = 0; i < 20 - it.first.length(); i++)
      {
        output += " ";
      }
      output += it.first + ":   " + to_string(it.second) + "\n";
      counter++;
    }
    else
    {
      for (size_t i = 0; i < 22 - it.first.length(); i++)
      {
        output += " ";
      }
      output += it.first + ":   " + to_string(it.second) + "\n";
    }
  }
  return output;
};
/*Struct ultilmate type
---------------------------*/
struct UltilType
{
  string url;
  map<string, int> wordsMap;
  map<string, int> commandsMap;
  AtcoCommand atcoCommands[1000];
  UltilType()
  {
  }
  UltilType(AtcoCommand arr[1000], map<string, int> &w, map<string, int> &c, string &u)
  {
    for (int i = 0; i < sizeof(arr); ++i)
    {
      atcoCommands[i] = arr[i];
    }
    wordsMap = w;
    commandsMap = c;
    url = u;
  }

  string getTopCommands(int amount)
  {
    return topCommands(commandsMap, amount, url);
  }

  string getTopWords(int amount)
  {
    return topWords(wordsMap);
  }

  void print()
  {
    for (size_t i = 0; i < 1000; i++)
    {
      if (atcoCommands[i].toString().length() > 10)
      {
        cout << atcoCommands[i].toString() << endl;
      }
    }
    cout << topWords(wordsMap) << endl;
    cout << topCommands(commandsMap, 20, url) << endl;
  }
};

/*Main method and check methods
---------------------------*/
bool exists_test1(const std::string &name)
{
  if (FILE *file = fopen(name.c_str(), "r"))
  {
    fclose(file);
    cout<<"Test url: OK"<<endl;
    return true;
  }
  return false;
};

bool checkDateTimeSplitMethod(UltilType input, string testString)
{
  if (input.atcoCommands[0].formattedDateTime.toString().substr(2, input.atcoCommands[0].formattedDateTime.toString().length() - 4).compare(testString) == 0)
  {
    cout << "Test split: OK" << endl;
    return true;
  }
  return false;
};

bool checkTopOcurrences(UltilType input, string testString)
{
  if (input.getTopCommands(20).compare(testString) == 0)
  {
    cout << "Test top occurences: OK" << endl;
    return true;
  }
  return false;
};

void readFile(string url, UltilType &output)
{
  map<string, int> wordsMap;
  map<string, int> commandsMap;
  AtcoCommand atcoCommands[1000];
  int index = 0;
  string line, fileName, wordSequence, commands;
  ifstream file(url);
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

    AtcoCommand atcoCommand = AtcoCommand(fileName, wordSequence, commands);
    atcoCommands[index++] = atcoCommand;
    file.close();

    for (size_t i = 0; i < 1000; i++)
    {
      wordsCount(atcoCommands[i].wordSequence, wordsMap);
      for (size_t k = 0; k < 6; k++)
      {
        wordsCount(atcoCommands[i].mainCommands[k], commandsMap);
      }
    }
    output = UltilType(atcoCommands, wordsMap, commandsMap, url);
  }
};

/*Main
---------------------------*/
int main()
{
  UltilType output;
  string url = "longTest.txt";
  string topCommands = readTextFile("testTopCommands.txt");
  if (!exists_test1(url))
  {
    cout << "File not exist, end game." << endl;
    return 0;
  }

  readFile(url, output);

  if (!checkDateTimeSplitMethod(output, "15-2-2019-11:32:2"))
  {
    cout << "Split method gone wrong." << endl;
    return 0;
  }

  if (!checkTopOcurrences(output, topCommands))
  {
    cout << "Top occurences method gone wrong." << endl;
    return 0;
  }

  cout << "Result: " << endl;
  output.print();
}