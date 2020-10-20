#include <iostream>

#include <ostream>

#include <algorithm>

#include <fstream>

#include <string>

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

    spliting(date, day, month, year);

    spliting(time, millisec, sec, min, hour);
  }

  void spliting(string date, int &day, int &month, int &year)
  {

    year = stoi(split(date, "-"));

    month = stoi(split(date, "-"));

    day = stoi(date);
  }

  void spliting(string time, int &millisec, int &sec, int &min, int &hour)
  {

    string out;
    hour = stoi(split(time, "-"));

    min = stoi(split(time, "-"));

    sec = stoi(split(time, "-"));

    millisec = stoi(time);
  }
  string split(string &line, string delimiter)
  {
    string key_word = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(key_word) + key_word.length() + 1);
    return key_word;
  }
  string abc;
  string toString()
  {

    return " (" + to_string(day) + "-" + to_string(month) + "-" + to_string(year) + "-" + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec) + ") :";
  }
};
struct AtcoCommand
{

  string file_Name;
  string word_Sequence;
  string commands[6];
  string date;
  string time;
  DateTime dateAndTime;

public:
  AtcoCommand()
  {
  }

public:
  AtcoCommand(string line)
  {
    // cout<<line<<"\n";

    getDateTime(line, date, time);
    dateAndTime = DateTime(date, time);
    // cout << date << " " << time << endl;
    file_Name += date + "__" + time + dateAndTime.toString();
    cout << file_Name << endl;
    getWordSequence(line, word_Sequence);
    getCommand(line, commands);

    //  for (int i = 0; i < 6; i++)
    //  {
    //    cout<<commands[i]<< " "<<endl;
    //  }
  }
  void getCommand(string &line, string commands[6])
  {
    string delimiter = " ";
    string key_word = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(key_word) + key_word.length());
    int commands_counter = 0;
    string copy = "";
    while (line.find(key_word) != -1)
    {
      copy = line.substr(0, line.find(key_word));
      line.erase(0, line.find(key_word) + key_word.length());
      commands[commands_counter++] = key_word + copy;
    }
    commands[commands_counter++] = key_word + line;
  }

  void getWordSequence(string &line, string &word_Sequence)
  {
    int counter = 0;
    while ((line[counter] >= 97 && line[counter] <= 122) || line[counter] == ' ')
    {
      word_Sequence += line[counter++];
    }
    line.erase(0, counter);
  }

  void getDateTime(string &line, string &date, string &time)
  {
    string delimiter = ":";
    string date_and_time = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + 2);
    delimiter = "__";

    date = date_and_time.substr(0, date_and_time.find(delimiter));
    time = date_and_time.substr(date_and_time.find(delimiter) + 2, date_and_time.length());
  }

  string tostring = "";
  string toString()
  {
    tostring += file_Name + " " + word_Sequence;

    string commands_Strings = "";
    for (int i = 0; i < 6; i++)
    {
      commands_Strings += commands[i];
    }
    tostring += commands_Strings;

    return tostring;
  }
};
int main()
{
  AtcoCommand atcTab[1000];
  int atcTab_index = 0;
  string word;
  string line;
  string text;

  int j = 0;

  bool test = true;
  ifstream myfile("inputText.txt");
  if (myfile.is_open())
  {
    while (myfile.good())
    {
      myfile >> word;

      if (word.size() == 24)
      {
        if (line.size() != 0)
        {
          AtcoCommand atc = AtcoCommand(line);
          // cout<<atc.toString()<< endl;
          atcTab[atcTab_index++] = atc;
          // cout<<line<<endl;
          //       text=line+"\n";
          line = "";
        }
        line += word + " ";
      }
      else
      {
        line += word + " ";
      }
    }
    //  cout<<line;
    AtcoCommand atc = AtcoCommand(line);
    // cout<<atc.toString();

    atcTab[atcTab_index++] = atc;
    myfile.close();
  }
  //  cout<<text;
  // for (size_t i = 0; i < 3; i++) {
  //   cout << atcTab[i].toString() << endl;
  // }

  return 0;
}