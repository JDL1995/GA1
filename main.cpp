#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "linkedList.h"
#include "ArgumentManager.h"
#include <algorithm>
using namespace std;

bool is_emptyFile(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
string reverseParentheses(string str)
{

    int length = str.length();
    int start = -1;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '(')
        {
            start = i; // start = 2
        }
        else if (str[i] == ')')
        {
            if (i == start + 1)
                return reverseParentheses(str.substr(0, start) + str.substr(i + 1));
            else
            {
                string reversed = str.substr(start + 1, i - start - 1);
                reverse(reversed.begin(), reversed.end());
                return reverseParentheses(str.substr(0, start) + reversed + str.substr(i + 1));
            }
        }
    }
    return str;
}



int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    // const string input = am.get("input");
    //  const string command  = am.get("command");
    // const string output = am.get("output");

    // ofstream ofs(output);
    // ifstream ifs(input);
    //  ifstream coms(command);

    ifstream inputfile("input3.txt");
    ofstream outputfile("output3.txt");
    //  ifstream commandfile("command3.txt");

    ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    ofstream output(am.get("output"));

    linkedlist list_bar1, list_bar2, allIDs;
    string line, value_str, reversedStr, currentBarcode;


    if (!is_emptyFile(input))
    {
        while (getline(input, line))
        {
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());

            if (line == "Bar1" || line == "Bar2")
                currentBarcode = line;

            if (currentBarcode == "Bar1")
            {
                do
                {
                    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                    if (line == "")
                        continue;
                    else if (line == "Bar2")
                    {
                        currentBarcode = line;
                        break;
                    }
                    else if (line != "Bar1")
                    {//borrowed following line from https://stackoverflow.com/questions/2346599/how-to-test-if-a-string-contains-any-digits-in-c
                        if (std::find_if(line.begin(), line.end(), (int(*)(int))std::isdigit) != line.end())
{
                         value_str = line;
                        reversedStr = reverseParentheses(value_str);
                        list_bar1.add_tail(reversedStr);
}
                        
                    }

                } while (getline(input, line));
            }
            else if (currentBarcode == "Bar2")
            {
                do
                {
                    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                    if (line == "")
                        continue;
                    else if (line == "Bar1")
                    {
                        currentBarcode = line;
                        break;
                    }
                    else if (line != "Bar2")
                    {//borrowed following line from https://stackoverflow.com/questions/2346599/how-to-test-if-a-string-contains-any-digits-in-c
                              if (std::find_if(line.begin(), line.end(), (int(*)(int))std::isdigit) != line.end())
{
                         value_str = line;
                        reversedStr = reverseParentheses(value_str);
                        list_bar1.add_tail(reversedStr);
}

                    }

                } while (getline(input, line));
            }
        }
        if(list_bar1.getSize()!=0){

        list_bar1.recursiveSort(list_bar1.getHead(), 0, 0, 0);
     //   list_bar2.recursiveSort(list_bar2.getHead(), 0, 0, 0);


    //    allIDs.recursiveSort(allIDs.getHead(), 0, 0, 0);
      //  allIDs.printrec_data1(allIDs.getHead());
        guiltyOI<linkedlist> *myGuiltyOI = new guiltyOI<linkedlist>;
        myGuiltyOI=list_bar1.recursiveGuilty<linkedlist>();
        bool arGs=false;
        if(myGuiltyOI->guilty->getSize()!=0){
            arGs=true;
                    output<<"Guilty:"<<endl;
                    cout<<"guiltylist: "<<endl;
                    myGuiltyOI->guilty->printrec_data1(myGuiltyOI->guilty->getHead());
                     myGuiltyOI->guilty->recursiveOut(output,myGuiltyOI->guilty->getHead());
        }
        cout<<"got here"<<endl;
        if(myGuiltyOI->innocent->getSize()!=0){
            if(arGs==true){
                output<<endl;
            }
            output<<"Innocent:"<<endl;
            cout<<"innocent list"<<endl;
        myGuiltyOI->innocent->printrec_data1(myGuiltyOI->innocent->getHead());
      myGuiltyOI->innocent->recursiveOut(output,myGuiltyOI->innocent->getHead());
        }
        output.close();
        
       // guiltyVerdict(allIDs.getHead());
      //  guiltyPrint(allIDs.getHead(), output);
    }else{
        output<<""<<endl;
    }
    
    }
    else{
        output<<""<<endl;
    }
    return 0;
}
