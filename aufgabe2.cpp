#include <ostream>
#include <sstream>
#include <iostream>

#include <algorithm>

#include <fstream>

#include<string>  

#include <iomanip> // wegen setw

#include <cassert> // wegen assert

using namespace std;


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
struct AtcoCommand
{
    
  string file_Name;
  string word_Sequence;
  string commands[6];
  string date;
  string time;
  DateTime dateAndTime;


    AtcoCommand(){

    }
    AtcoCommand(string dateTime , string word_Sequence1 , string commands1){

          date_and_time(dateTime, date, time);
        dateAndTime =DateTime(date, time);
        file_Name=date+"__"+time+" "+ dateAndTime.toString();
        word_Sequence=word_Sequence1;
         command(commands1, commands);
    }

  void date_and_time(string line, string & date, string & time) {
    string delimiter = ":";
    string date_and_time = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) );
    delimiter = "__";

    date = date_and_time.substr(0, date_and_time.find(delimiter));
    time = date_and_time.substr(date_and_time.find(delimiter) + 2, date_and_time.length());
  }



    void command(string commands1, string commands[]) {
        int commands_counter=0;
    istringstream f(commands1);
    string line;  

    while (getline(f, line)) {
      
    commands[commands_counter++]=line;
    }
  }

    string toString() {
        string tostring;
    // return file_Name + word_Sequence;
    tostring += file_Name + " \n " +  word_Sequence+": \n " ;

    string commands_Strings = "";
    for (int i = 0; i < 6; i++) {
      if(commands[i].length()<2 ){
          break;
      }
      commands_Strings += commands[i] +";";
      
    }
    tostring += commands_Strings;

    return tostring;

  }
};



int main() {

  AtcoCommand atcTab[1000];
  int atcTab_index = 0;
     string line;
    string file_Name;
    string word_Sequence;
    string commands; 
  int j = 0;
    int k=0;
  bool test = true;
  ifstream myfile("D:\\9raya\\c++\\exemple.txt");

  if (myfile.is_open()) {
    while (myfile.good()) {
          getline (myfile,line);
       
    //   cout<<line<<endl; 
  
   if(line.find(":")!=-1){
      if(word_Sequence.length()!=0){
          AtcoCommand atc =  AtcoCommand(file_Name,word_Sequence,commands);
          atcTab[atcTab_index++]=atc; 
         
          commands="";
      }
       file_Name=line;
       j++;
       

   }else if (j==1){
    //    cout<<line;
       word_Sequence=line;
    // cout<<word_Sequence<<endl;

       j=0;
   }else{
        // cout<<line<<endl;
       commands+=line+"\n ";
     
   }
    }
    }
   
      AtcoCommand atc =  AtcoCommand(file_Name,word_Sequence,commands);
       atcTab[atcTab_index++]=atc; 

     myfile.close();
//   }
//   cout<<text;
  
for (size_t i = 0; i < 1000; i++) {
    if(atcTab[i].toString().length()<8){
        break;
    }
   cout<< atcTab[i].toString()<<endl;
 }
// cout<<sequenceTest("2019-02-15__11-32-02-00:  speedbird five two charlie climb flight level two two zero BAW52CV CLIMB 120 FL BAW52CV INIT_RESPONSE", "speedbird five two charlie climb flight level two two zero");


  return 0;
}