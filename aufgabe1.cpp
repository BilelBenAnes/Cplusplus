#include <iostream>

#include <ostream>

#include <algorithm>

#include <fstream>

#include<string>  

#include <iomanip> // wegen setw

#include <cassert> // wegen assert

using namespace std;

struct DateTime {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int millisec;

  DateTime() {

  }
  DateTime(string date, string time) {

    spliting(date, day, month, year);

    spliting(time, millisec, sec, min, hour);
  
  }

  void spliting(string date, int & day, int & month, int & year) {

    year = stoi(split(date, "-"));

    month = stoi(split(date, "-"));

    day = stoi(date);

  }

  void spliting(string time, int & millisec, int & sec, int & min, int & hour) {


    
    hour = stoi(split(time, "-"));

    min = stoi(split(time, "-"));

    sec = stoi(split(time, "-"));

    millisec = stoi(time);

  }
  string split(string & line, string delimiter) {
    string key_word = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(key_word) + key_word.length() + 1);
    return key_word;
  }

  string toString(){
   
    return  " ("+to_string(day) +"-"+to_string(month)+"-"+to_string(year)+"-"+to_string(hour)+":"+to_string(min)+":"+to_string(sec)+ "):" ;
     
  
    
  }

}; 
struct AtcoCommand {

  string file_Name;
  string word_Sequence;
  string commands[6];
  string date;
  string time;
  DateTime dateAndTime;

  public: AtcoCommand() {

  }
  public: AtcoCommand(string line) {
  //  cout<<line<<"\n";
cout<<line<<endl;
    date_and_time(line, date, time);
    dateAndTime = DateTime(date, time);

    file_Name += date + "__" + time+ dateAndTime.toString() ;
   //cout<<file_Name<<endl;
  //  word_Sequence=sequence(line);
    sequence(line, word_Sequence);
    if(line.length()!=0){

    command(line, commands);
    }

    //  for (int i = 0; i < 6; i++)
    //  {
    //    cout<<commands[i]<< " "<<endl;
    //  }

  }
  void command(string & line, string commands[6]) {
    string delimiter = " ";
    string key_word = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(key_word) + key_word.length());
    int commands_counter = 0;
    string copy = "";
    while (line.find(key_word) != -1) {
      copy = line.substr(0, line.find(key_word));
      line.erase(0, line.find(key_word) + key_word.length());
      commands[commands_counter++] = key_word + copy;
    }
    commands[commands_counter++] = key_word + line;
  }

    void sequence(string & line1 , string & word_Sequence) {
      // string word_Sequence;
    int counter = 3;
    while ((line1[counter] >= 97 && line1[counter] <= 122) || line1[counter] == ' ' ) {
      word_Sequence += line1[counter++];
    }
  //    cout<< word_Sequence<<endl;
    line1.erase(0, counter);
    //cout<<"sequence line   "<< line1<<" sequence word "<<word_Sequence <<endl;
    
   // return word_Sequence;
  }

  void date_and_time(string & line, string & date, string & time) {
    string delimiter = ":";
    string date_and_time = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) );
    delimiter = "__";

    date = date_and_time.substr(0, date_and_time.find(delimiter));
    time = date_and_time.substr(date_and_time.find(delimiter) + 2, date_and_time.length());
  }

  string tostring = "";
  string toString() {
    // return file_Name + word_Sequence;
    tostring += file_Name + " "+  word_Sequence;

    string commands_Strings = "";
    for (int i = 0; i < 6; i++) {
      commands_Strings += commands[i];
      
    }
    tostring += commands_Strings;

    return tostring;

  }

};

// bool testInit() {
//    Vektor v;
//    v.dimension=4;
//    const int wert=81;
//    Init(v, wert);
//    for (int i=0; i<v.dimension; ++i)   {
//       if (v.daten[i] != wert) {
//          return false;
//       }
//    }
//    return true;
// }

bool sequenceTest(string line, string sequence){

    AtcoCommand test=  AtcoCommand(line);

  cout<< test.word_Sequence<<endl;
  //cout<<line<<endl;
  if(sequence.compare(test.word_Sequence)==0){

    return true;
  }

  return false;
}


bool commandTest( string date, string delimiter) {
   
  AtcoCommand test=  AtcoCommand(date);
     for (int i = 0; i < 6; i++)
     {
       cout<<test.commands[i]<< " "<<endl;
     }
 

    

  // if (year.compare("2019") == 0){

  //  return true;
   
  // }

  return false;
}

bool splitTest( string date, string delimiter) {
   

  
  DateTime d=DateTime();
  string year=d.split(date,delimiter);
    // cout<<"2019"<<"="<<year;
  if (year.compare("2019") == 0){

   return true;
   
  }

  return false;
}









int main() {

  AtcoCommand atcTab[1000];
  int atcTab_index = 0;
  string word;
  string line;
  string text;

  int j = 0;

  bool test = true;
  ifstream myfile("D:\\9raya\\c++\\exemple 2.txt");
  if (myfile.is_open()) {
    while (myfile.good()) {
      myfile >> word;

      if (word.size() == 24) {
        if (line.size() != 0) {
          AtcoCommand atc =  AtcoCommand(line);
          // cout<<atc.toString()<< endl;
          atcTab[atcTab_index++] = atc;
          line = "";
        }
        line += word + " ";

      } else  {
        line += word + " ";

      }
      
    }
    AtcoCommand atc = AtcoCommand(line);
    atcTab[atcTab_index++] = atc;
    myfile.close();
  }
  cout<<text;
  for (size_t i = 0; i < 3; i++) {
    cout << atcTab[i].toString() << endl;
  }
// cout<<sequenceTest("2019-02-15__11-32-02-00:  speedbird five two charlie climb flight level two two zero BAW52CV CLIMB 120 FL BAW52CV INIT_RESPONSE", "speedbird five two charlie climb flight level two two zero");


  return 0;
}