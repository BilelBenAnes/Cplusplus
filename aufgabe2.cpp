#include <ostream>
#include <sstream>
#include <iostream>

#include <algorithm>

#include <fstream>

#include<string>  

#include <iomanip> // wegen setw

#include <cassert> // wegen assert

using namespace std;
struct AtcoCommand
{
    
  string file_Name;
  string word_Sequence;
  string commands[6];
  string date;
  string time;
 // DateTime dateAndTime;


    AtcoCommand(){

    }
    AtcoCommand(string file_Name1 , string word_Sequence1 , string commands1){
        file_Name=file_Name1;
        word_Sequence=word_Sequence1;
         command(commands1, commands);
    }


    void command(string commands1, string commands[6]) {
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
    tostring += file_Name + " "+  word_Sequence;

    string commands_Strings = "";
    for (int i = 0; i < 6; i++) {
      
      commands_Strings += commands[i];
      
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
  ifstream myfile("D:\\9raya\\c++\\exemple 2.txt");

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
    //  cout<<line<<"***"<<endl;
       file_Name=line;
      // cout<<file_Name<<endl;
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
    //   istringstream f(commands);
    // string line;    
    // while (getline(f, line)) {
    //    cout<<line<<endl;

    // }
   
    //   } else {
    //     line += word + " ";

    //   }

//     AtcoCommand atc = AtcoCommand(line);
//     atcTab[atcTab_index++] = atc;
     myfile.close();
//   }
//   cout<<text;
  
for (size_t i = 0; i < 10; i++) {
   cout<< atcTab[i].toString()<<endl;
 }
// cout<<sequenceTest("2019-02-15__11-32-02-00:  speedbird five two charlie climb flight level two two zero BAW52CV CLIMB 120 FL BAW52CV INIT_RESPONSE", "speedbird five two charlie climb flight level two two zero");


  return 0;
}