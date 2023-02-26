#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "linkedlist.h"
#include "ArgumentManager.h"
#include <algorithm>
using namespace std;

bool is_emptyFile(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

string reverseParentheses(string str)
{
    // str = "10(01)"
    //int num_pairs = std::count(str.begin(), str.end(), '(');
    //cout << "Number of pairs of parenthesises: " << num_pairs << endl;
    int length = str.length(); // length = 6
    int start = -1;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '(')
        {
            start = i; // start = 2
        }
        else if (str[i] == ')')
        {
            string reversed = str.substr(start + 1, i - start - 1);
            reverse(reversed.begin(), reversed.end());
            return reverseParentheses(str.substr(0, start) + reversed + str.substr(i + 1));
        }
    }

    //std::cout << "|" << str << "|" << endl;
    return str;
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    // const string input = am.get("input");
    //  const string command  = am.get("command");
    // const string output = am.get("output");

    // ofstream ofs(output);
    // ifstream ifs(input//);
    //  ifstream coms(command);

    ifstream inputfile("input1.txt");
    ofstream outputfile("output1.txt");
    //  ifstream commandfile("command3.txt");

    ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    ofstream output(am.get("output"));

    linkedlist<string,int> list_bar1, list_bar2, list_bar1_sorted, list_bar2_sorted;
    vector<string> vect1, vect2;
    string line, value_str, reversedStr, currentBarcode;
    int value;

    if (!is_emptyFile(inputfile))
    {
        while (getline(inputfile, line))
        {
            line.erase(remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());

            cout << "line currently is: |" << line << "|" << endl;

            if (line == "Bar1" || line == "Bar2")
            {
                currentBarcode = line;
                cout << "currentBarcode is now: " << currentBarcode << endl;
            }

            if (currentBarcode == "Bar1")
            {
                cout << "entering do-while loop for bar 1" << endl;
                do
                {
                    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                    cout << "line currently is: |" << line << "|" << endl;

                    if (line == "")
                    {
                        cout << "line was empty. Skipping to next line" << endl;
                        continue;
                    }

                    else if (line == "Bar2")
                    {
                        currentBarcode = line;
                        cout << "currentBarcode is now: " << currentBarcode << endl;
                        cout << "breaking out of do-while loop for bar 1" << endl;
                        break;
                    }
                    else if (line != "Bar1")
                    {
                        value_str = line;
                        cout << "Pushing the following to vect1: |" << value_str << "|" << endl;
                        vect1.push_back(value_str);
                    }

                } while (getline(inputfile, line));
            }
            else if (currentBarcode == "Bar2")
            {
                cout << "entering do-while loop for bar 2" << endl;
                do
                {
                    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                    cout << "line currently is: |" << line << "|" << endl;

                    if (line == "")
                    {
                        cout << "line was empty. Skipping to next line" << endl;
                        continue;
                    }
                    else if (line == "Bar1")
                    {
                        currentBarcode = line;
                        cout << "currentBarcode is now: " << currentBarcode << endl;
                        cout << "breaking out of do-while loop for bar 2" << endl;
                        break;
                    }
                    else if (line != "Bar2")
                    {
                        value_str = line;
                        cout << "Pushing the following to vect2: |" << value_str << "|" << endl;
                        vect2.push_back(value_str);
                    }

                } while (getline(inputfile, line));
            }
        }

        cout << endl;

        cout << "Vector 1 size: " << vect1.size() << endl;
        for (int i = 0; i < vect1.size(); i++)
        {   
            reversedStr = reverseParentheses(vect1[i]);
            // string reversedStr = list_bar1.reverseParentheses(vect1[i]);
            cout << "original string : " << vect1[i] << endl;
            cout << "reversed string pushed to list_bar1: " << reversedStr << endl;
            value = stoi(reversedStr);
            cout << "value of string as an integer pushed to list_bar1: " << value << endl;
            list_bar1.add_tail(reversedStr, value);
        }

        cout << "List_bar_1 size: " << list_bar1.getSize() << endl;
        cout << endl
             << "printing list_bar1" << endl
             << endl;
        list_bar1.printrec_data1(list_bar1.getHead());
        cout << endl;

        cout << "Vector 2 size: " << vect2.size() << endl;
        for (int i = 0; i < vect2.size(); i++)
        {
            reversedStr = reverseParentheses(vect2[i]);
            // string reversedStr = list_bar2.reverseParentheses(vect2[i]);
            cout << "original string : " << vect2[i] << endl;
            cout << "reversed string pushed to list_bar2: " << reversedStr << endl;
            value = stoi(reversedStr);
            cout << "value of string as an integer pushed to list_bar2: " << value << endl;
            list_bar2.add_tail(reversedStr, value);
        }

        cout << "List_bar_2 size: " << list_bar1.getSize() << endl;
        cout << endl
             << "printing list_bar2" << endl
             << endl;
        list_bar2.printrec_data1(list_bar2.getHead());
        cout << endl;
        //cout << "Data value of the head of list_bar1:  " << list_bar1.getHead()->data << endl;
        //cout << "Data value of the head of list_bar2:  " << list_bar1.getHead()->data << endl;
        //list_bar1_sorted.add_tail(list_bar1.insertionSort_recursive(list_bar1.getHead()));
        //list_bar2_sorted.add_tail(list_bar2.insertionSort_recursive(list_bar2.getHead()));

        cout << endl
             << "printing all data1 of list_bar1 after sorting" << endl
             << endl;
        list_bar1.printrec_data1(list_bar1.getHead());
        cout << endl;

        cout << endl
             << "printing all data2 of list_bar1 after sorting" << endl
             << endl;
        list_bar1.printrec_data2(list_bar1.getHead());
        cout << endl;

        cout << endl
             << "printing all data1 of list_bar2 after sorting" << endl
             << endl;
        list_bar2.printrec_data1(list_bar2.getHead());
        cout << endl;

        cout << endl
             << "printing all data2 of list_bar2 after sorting" << endl
             << endl;
        list_bar2.printrec_data2(list_bar2.getHead());
        cout << endl;

        

    }
    return 0;
}
