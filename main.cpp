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
void guiltyVerdict(Node *head) // will need take in all of the IDs (sorted)
{
    Node *cur = head;
    Node *search = nullptr;
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }
    while (cur != nullptr)
    {
        search = cur->next;
        while (search != nullptr)
        {
            if (stoi(search->data) == stoi(cur->data))
            {
                cur->guilty = true;
                search->guilty = true;
            }
            search = search->next;
        }
        cur = cur->next;
    }
}
void guiltyPrint(Node *head, ofstream &outputFile) // will also need to take in all IDs sorted
{
    Node *cur = head;
    Node *checker = head;
    bool g, i;
    while (checker != nullptr)
    {
        if (checker->guilty)
        {
            g = true;
        }
        else if (!checker->guilty)
        {
            i = true;
        }
        checker = checker->next;
    }

    if (g)
    {
        outputFile << "Guilty:\n";
        if (head->guilty)
        {
            outputFile << head->data << std::endl;
            cur = cur->next;
        }

        while (cur != nullptr)
        {
            if (cur->guilty && (cur->prev->data != cur->data))
            {
                outputFile << cur->data << std::endl;
            }
            cur = cur->next;
        }
    }

    if (i)
    {
        cur = head;
        outputFile << "Innocent:\n";
        while (cur != nullptr)
        {
            if (!cur->guilty)
            {
                outputFile << cur->data << std::endl;
            }
            cur = cur->next;
        }
    }
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
                    {
                        value_str = line;
                        reversedStr = reverseParentheses(value_str);
                        list_bar1.add_tail(reversedStr);
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
                    {
                        value_str = line;
                        reversedStr = reverseParentheses(value_str);
                        list_bar2.add_tail(reversedStr);

                    }

                } while (getline(input, line));
            }
        }

        list_bar1.recursiveSort(list_bar1.getHead(), 0, 0, 0);
        list_bar2.recursiveSort(list_bar2.getHead(), 0, 0, 0);

        Node *tempHead = list_bar1.getHead();
        while (tempHead != nullptr)
        {
            allIDs.add_tail(tempHead->data);
            tempHead = tempHead->next;
        }

        tempHead = list_bar2.getHead();
        while (tempHead != nullptr)
        {
            allIDs.add_tail(tempHead->data);
            tempHead = tempHead->next;
        }

        allIDs.recursiveSort(allIDs.getHead(), 0, 0, 0);

        guiltyVerdict(allIDs.getHead());
        guiltyPrint(allIDs.getHead(), output);
    }
    return 0;
}
