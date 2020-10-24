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
struct Occurence{
  int  occuranceNumber=0;
  string word="";
  Occurence(){

  }

};

    bool ValueCmp(Occurence const & a, Occurence const & b)
        {
       // cout<<a.occuranceNumber<<endl;    
    return a.word >b.word;
        }

main (){
Occurence tab[10];
    tab[0].occuranceNumber=4;
    tab[0].word="aaaa";

    tab[1].occuranceNumber=6;
    tab[1].word="bbbb";

    tab[2].occuranceNumber=1;
    tab[2].word="cccc";

    tab[3].occuranceNumber=5;
    tab[3].word="dddd";


     int n = sizeof(tab)/sizeof(*tab);
   //  cout<<n;
//     cout<<tab<<endl;
//    cout<<tab+n; 
  //   cout<<"fsdsdfffffffff";
//    for (size_t i = 0; i < 5; i++)
//     {
//       cout<<tab[i].word<<endl;;
//     }
string line="dfdsfsdf";
for (auto &ch :line)
{
 cout<<ch<<endl;
}
    //   sort(tab, tab+n,ValueCmp); 
    // // cout<<"fsdsdf";
    // for (size_t i = 0; i < 10; i++)
    // {
    //   cout<<tab[i].word<<" "<<tab[i].occuranceNumber<<endl;;
    // }
    return 0;
}