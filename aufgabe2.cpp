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

  string toString() {

    return " (" + to_string(day) + "-" + to_string(month) + "-" + to_string(year) + "-" + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec) + "):";

  }

};
struct AtcoCommand {

  string file_Name;
  string word_Sequence;
  string commands[6];
  string date;
  string time;
  DateTime dateAndTime;
  string testdatetime;

  AtcoCommand() {

  }
  AtcoCommand(string dateTime, string word_Sequence1, string commands1) {
    // cout<<dateTime;
    testdatetime = dateTime;
    date_and_time(dateTime, date, time);
    dateAndTime = DateTime(date, time);
    file_Name = date + "__" + time + " " + dateAndTime.toString();
    word_Sequence = word_Sequence1;
    command(commands1, commands);
  }

  void date_and_time(string line, string & date, string & time) {
    string delimiter = ":";
    string date_and_time = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter));
    delimiter = "__";

    date = date_and_time.substr(0, date_and_time.find(delimiter));
    time = date_and_time.substr(date_and_time.find(delimiter) + 2, date_and_time.length());
  }

  void command(string commands1, string commands[]) {
    int commands_counter = 0;
    istringstream f(commands1);
    string line;

    while (getline(f, line)) {

      commands[commands_counter++] = line;
    }
  }

  string toString() {
    string tostring;

    tostring += file_Name + " \n " + word_Sequence + ": \n ";

    string commands_Strings = "";
    for (int i = 0; i < 6; i++) {
      if (commands[i].length() < 2) {
        break;
      }
      commands_Strings += commands[i] + ";";

    }
    tostring += commands_Strings;

    return tostring;

  }
};

struct Occurence {
  int occuranceNumber = 0;
  string word = "";
  Occurence() {

  }
  string toString() {

    return word +" "+ to_string(occuranceNumber);
  }

};
bool splitTest(string date, string delimiter) {

  DateTime d = DateTime();
  string year = d.split(date, delimiter);
  // cout<<"2019"<<"="<<year;
  if (year.compare("2019") == 0) {

    return true;

  }
  return false;
}

void readingFromFile(string filePath, AtcoCommand atcTab[]) {
  // cout<<filePath;
  int atcTab_index = 0;
  string line;
  string file_Name;
  string word_Sequence;
  string commands;
  int j = 0;
  ifstream myfile(filePath);
  if (myfile.is_open()) {
    while (myfile.good()) {
      getline(myfile, line);

      if (line.find(":") != -1) {
        if (word_Sequence.length() != 0) {
          AtcoCommand atc = AtcoCommand(file_Name, word_Sequence, commands);
          atcTab[atcTab_index++] = atc;

          commands = "";
        }
        file_Name = line;
        j++;

      } else if (j == 1) {

        word_Sequence = line;

        j = 0;
      } else {

        commands += line + "\n";

      }
    }
  }

  AtcoCommand atc = AtcoCommand(file_Name, word_Sequence, commands);
  atcTab[atcTab_index++] = atc;
 
  
  myfile.close();
}

bool commandTest(string filePath, string test) {

  AtcoCommand atcTestTab[1000];
  string command;
  readingFromFile(filePath, atcTestTab);

  // cout<<"dfdf";

  for (size_t i = 0; i < 6; i++) {
    if (atcTestTab[0].commands[i] == "") {
      break;
    }
    command += atcTestTab[0].commands[i];
  }
  // cout<<command<<endl;
  if (command.compare(test) == 0) {
    return true;
  }

  return false;
}

int find(string word, Occurence tab[]) {
  for (int i = 0; i < 10000; i++) {
    if (tab[i].word.compare(word) == 0) {
      return i;
    }

  }
  return -1;
}

bool sortByNumbers(Occurence const & a, Occurence const & b)
  {
  // cout<<a.occuranceNumber<<endl;    
  return a.occuranceNumber >b.occuranceNumber;
}
 void systemOut(Occurence tab[], int size){

     cout<<"the top 20 occurences specified in expected.txt \n";
  for (size_t i = 0; i < size; i++) {
    if( tab[i].word==""){
      break;
    }
  if(i<3){
       printf(" %i.%20s:   %i \n", i+1, tab[i].word.c_str(),tab[i].occuranceNumber );
    }else{

    printf("   %20s:   %i \n", tab[i].word.c_str(),tab[i].occuranceNumber );
    }
  }
}

string toString(Occurence tab[], int size){
  string line="";
    for (size_t i = 0; i < size; i++)
    {
      if(i!=size-1){

     line+=tab[i].toString()+" ";
      }else{
        line+=tab[i].toString();
      }
    }
    
    return line;
}



Occurence*  topTen(AtcoCommand atcTab[]) {
  Occurence  *top10=new Occurence[10];
  Occurence tab[10000];
  int commands_counter = 0;
  for (size_t i = 0; i < 1000; i++) {
    string word_sequence = atcTab[i].word_Sequence;
    istringstream f(word_sequence);
    string word;

    while (f >> word) {
      // cout<<word<<endl;

      int position = find(word, tab);
      if (position != -1) {

        tab[position].occuranceNumber++;

      } else {

        tab[commands_counter].word = word;
        tab[commands_counter++].occuranceNumber++;

      }
    }
  }

  int n = sizeof(tab) / sizeof( * tab);
  sort(tab, tab + n, sortByNumbers);
  for (size_t i = 0; i < 10; i++) {
    top10[i].occuranceNumber = tab[i].occuranceNumber;
    top10[i].word = tab[i].word;
  }

   return top10;

}

bool sequenceTest(string filePath, string test) {

  AtcoCommand atcTestTab[1000];
  readingFromFile(filePath, atcTestTab);

  if (atcTestTab[0].word_Sequence.compare(test) == 0) {
    return true;
  }

  return false;
}

bool dateTimeTest(string filePath, string test) {
  string datetime;
  AtcoCommand atcTestTab[1000];
  readingFromFile(filePath, atcTestTab);
  datetime = atcTestTab[0].date + "__" + atcTestTab[0].time + ":";

  if (atcTestTab[0].testdatetime.compare(test) == 0) {
    return true;
  }

  return false;
}


bool top10Test(string filePath, string test){
    AtcoCommand atcTab[1000];
    string top10String="";
  Occurence* top10;
    readingFromFile(filePath, atcTab  );
    top10= topTen(atcTab);
    top10String=toString(top10,10 );
if(top10String.compare(test)==0){
  return true;
}
return false;

}
Occurence* readingExpected( string filePath , int &size){
      Occurence *expectedType=new Occurence[10];

     int counter=0;
      string line="";
    ifstream myfile(filePath);
  if (myfile.is_open()) {
    while (myfile.good()) {
      getline(myfile, line);
     myfile.close();
     }
    }
    int expectedTypeCounter=0;
    // cout<<line;
     while (line.find(",")!=-1 ) {
       expectedType[counter].occuranceNumber=0;
       expectedType[counter++].word= line.substr(0, line.find(","));
       line.erase(0, line.find(",") +1);
    }
    if(line.length()!=0){
      expectedType[counter].occuranceNumber=0;
       expectedType[counter++].word= line;
    }
  
  Occurence *expectedTypeReturn=new Occurence[counter];
  for (size_t i = 0; i < counter; i++)
  {
   expectedTypeReturn[i]=expectedType[i];
  }
     size=counter;
  return expectedTypeReturn;
}






Occurence *  topTwenty(AtcoCommand atcTab[], string filePath ) {
    Occurence* expectedType;
    int size;
    // string name=extractingname
   expectedType = readingExpected(filePath,size);
  Occurence* top20=new Occurence[8];
  for (size_t i = 0; i < 1000; i++) {
     if(atcTab[i].file_Name==""){
       break;
     }
      for (size_t j = 0; j < 6; j++)
      {
         string command = atcTab[i].commands[j];
      for (size_t k = 0; k < 10; k++)
      {
       if(command.find(expectedType[k].word)!=-1){
         expectedType[k].occuranceNumber++;
       }
      }

    }
  }

  sort(expectedType, expectedType + size, sortByNumbers);
// cout<<"the top 20 occurences specified in expected.txt \n";
    for (int i = 0; i < size; i++) {
    top20[i].occuranceNumber =expectedType[i].occuranceNumber;
    top20[i].word = expectedType[i].word;
    string temp=top20[i].word;
    // cout<<temp<<endl;
    // if(i<3){
    //    printf(" %i.%20s:   %i \n", i+1, temp.c_str(),top20[i].occuranceNumber );
    // }else{

    // printf("   %20s:   %i \n", temp.c_str(),top20[i].occuranceNumber );
    // }
    // cout<<top20[i].word<<"  "<< top20[i].occuranceNumber<<endl;
  }
  return top20;

}

bool top20Test(string filePath, string test20,AtcoCommand atcTab[] ){
    string top20String="";
    Occurence *top20;

    top20= topTwenty(atcTab,filePath);
    // for (size_t i = 0; i <5; i++)
    // {
    //   cout<<top20[i].toString();
    // }
    
  top20String=toString(top20,5 );
if(top20String.compare(test20)==0){
  return true;
}
return false;
}

string extractingName(string filePath){



  return "";
}

int main() {

  AtcoCommand atcTab[1000];
    readingFromFile( "exemple.txt",atcTab);

    Occurence * top10;
   Occurence * top20;
   string expectedFilepath="expected.txt";
 string test10="two 3 charlie 2 five 1 speedbird 1 morning 1 good 1 zero 1 level 1 flight 1 climb 1";
 top20=topTwenty(atcTab,expectedFilepath);
 systemOut(top20,20);
  // cout<<"\n";

//    string test20="INIT_RESPONSE 1  CLIMB 1  NO_CONCEPT 1  FL 1  ABC 0";
//   // cout<<test20.length()<<"main"<<endl;
// bool test1=top20Test("D:\\9raya\\c++\\expected.txt", test20,atcTab);
// // string k=toString(top20,5);
// // cout<<k<<endl;
// cout<<test1;



  //  cout<< top10Test( "D:\\9raya\\c++\\exemple.txt", "");
  // for (size_t i = 0; i < 10; i++)
  // {
  //   if(top20[i].word==""){
  //     break;
  //   }
  //   cout<<top20[i].word<<" "<<top20[i].occuranceNumber<<endl;
  //   /* code */
  // }
 // cout<< top20->toString();
  // delete [] top10;

  return 0;
}