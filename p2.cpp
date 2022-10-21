// NAME: Jordan Chan
// PROGRAM: p2.cpp
// PURPOSE: The purpose of the program is to implement a BST template class and test it with the driver program, using
// integers and strings as the test data types.
// INPUT: Program reads in two files of data, one of integer values and one of strings
// PROCESS: The driver program makes calls to the BST class in order to implement different functions. These functions
// each have a specific purpose to alter or analyze the BST for any data type, but in this program specifically: for
// integers and strings.
// OUTPUT: Program outputs various analysis of the BST, including preorder, inorder, postorder traversals, height, size,
// number of leaves, number of nodes, level of a node, ancestors of a node, etc.

#include <iostream>
#include "BST.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// letters to form random words for string BST
static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
int stringLength = sizeof(alphanum) - 1;

char genRandom()  // Random string generator function.
{
    return alphanum[rand() % stringLength];
}

int main() {
/**
 * main function composed of integer BST and string BST; reads in files to populate both BSTS; calls various functions
 * from the BST class in order to provide information and carry out actions on both the integer BST and string BST;
 * functions include inserting new nodes, removing nodes, listing the height, number of leaves, number of nodes, the
 * preorder, inorder, and postorder traversals
 */
    cout << "\nWelcome to the Binary Search Tree Program!\n" << endl;
    cout << "******************************\n" <<
            "* INTEGER BINARY SEARCH TREE *\n" <<
            "******************************\n" << endl;

    BST<int> intBST;

    string empty;
    if (intBST.empty())
        empty = "true";
    else
        empty = "false";

    cout << "** CREATE BST **" <<
         "\n# of nodes: " << intBST.size() <<
         "\n# of leaves: " << intBST.getLeafCount() <<
         "\nBST height: " << intBST.getHeight() <<
         "\nBST empty? " << empty << endl;

    string fileN, data;
    cout << "Enter integer file: ";
    cin >> fileN;

    ifstream inFile;
    inFile.open(fileN);

    cout << "\n** TEST INSERT **" <<
            "\nInserting in this order: ";

    if (!inFile.fail()) {
        while (getline(inFile, data)) {
            int dataAsInt = stoi(data);
            cout << dataAsInt << " ";
            intBST.insert(dataAsInt);
        }
    }
    else
        cout << "error opening file";

    string empty2;
    if (intBST.empty())
        empty2 = "true";
    else
        empty2 = "false";

    cout << "\n# of nodes: " << intBST.size() <<
            "\n# of leaves: " << intBST.getLeafCount() <<
            "\nBST height: " << intBST.getHeight() <<
            "\nBST empty? " << empty2 << endl;

    cout << "\n** TEST TRAVERSALS **" <<
            "\npre-order:   " << intBST.getPreOrderTraversal() <<
            "\nin-order:    " << intBST.getInOrderTraversal() <<
            "\npost-order:  " << intBST.getPostOrderTraversal() << endl;

    cout << "\n** TEST LEVEL & ANCESTORS **" << endl;
    string preOrder = intBST.getPreOrderTraversal();
    stringstream ss;
    ss << preOrder;
    string line;

    while (getline(ss, line, ' ')) {
        int indivInt = stoi(line);
        cout << "level(" << indivInt << "): " << intBST.getLevel(indivInt) <<
                ", ancestors(" << indivInt << "): " << intBST.getAncestors(indivInt) << endl;
    }

    cout << "\n** TEST CONTAINS **" << endl;
    srand(time(NULL));
    stringstream sstr;
    int size = intBST.size();
    for (int i = 0; i <= size; i++) {
        int randomNum = 1 + (rand() % 100);
        bool doesContain = intBST.contains(randomNum);
        if (doesContain)
            cout << "contains(" << randomNum << "): true" << endl;
        else
            cout << "contains(" << randomNum << "): false" << endl;

        sstr << randomNum << " ";
        intBST.remove(randomNum);
    }

    cout << "\n** TEST REMOVE **" << endl;
    cout << "Removing in this order: " << sstr.str() << endl;
    // removed above

    string empty3;
    if (intBST.empty())
        empty3 = "true";
    else
        empty3 = "false";

    cout << "# of nodes: " << intBST.size() <<
            "\n# of leaves: " << intBST.getLeafCount() <<
            "\ntree height: " << intBST.getHeight() <<
            "\ntree empty? " << empty3 <<
            "\npre-order: " << intBST.getPreOrderTraversal() <<
            "\nin-order: " << intBST.getInOrderTraversal() <<
            "\npost-order: " << intBST.getPostOrderTraversal() << endl;

    cout << "\n** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: " << sstr.str() << endl;

    string eachNum;
    while (getline(sstr, eachNum, ' ')) {
        int numAsInt = stoi(eachNum);
        intBST.insert(numAsInt);
    }

    string empty4;
    if (intBST.empty())
        empty4 = "true";
    else
        empty4 = "false";

    cout << "# of nodes: " << intBST.size() <<
             "\n# of leaves: " << intBST.getLeafCount() <<
             "\ntree height: " << intBST.getHeight() <<
             "\ntree empty? " << empty4 <<
             "\npre-order: " << intBST.getPreOrderTraversal() <<
             "\nin-order: " << intBST.getInOrderTraversal() <<
             "\npost-order: " << intBST.getPostOrderTraversal() << endl;


    cout << "\n********************\n" <<
             "* test string BST  *\n" <<
             "********************\n" << endl;

    BST<string> strBST;

    string empty5;
    if (strBST.empty())
        empty5 = "true";
    else
        empty5 = "false";

    cout << "** CREATE BST **" <<
            "\n# of nodes: " << strBST.size() <<
            "\n# of leaves: " << strBST.getLeafCount() <<
            "\nBST height: " << strBST.getHeight() <<
            "\nBST empty? " << empty5 << endl;

    string fileNstr, dataStr;
    cout << "Enter string file: ";
    cin >> fileNstr;

    ifstream inFileStr;
    inFileStr.open(fileNstr);

    cout << "\n** TEST INSERT **" <<
            "\nInserting in this order: ";

    if (!inFileStr.fail()) {
        while (getline(inFileStr, dataStr)) {
            cout << dataStr << " ";
            strBST.insert(dataStr);
        }
    }
    else
        cout << "Error opening file.";

    cout << "\n** TEST TRAVERSALS **" <<
         "\npre-order:   " << strBST.getPreOrderTraversal() <<
         "\nin-order:    " << strBST.getInOrderTraversal() <<
         "\npost-order:  " << strBST.getPostOrderTraversal() << endl;

    cout << "\n** TEST LEVEL & ANCESTORS **" << endl;
    string preOrderStr = strBST.getPreOrderTraversal();
    stringstream sstring;
    sstring << preOrderStr;
    string lineStr;

    while (getline(sstring, lineStr, ' ')) {
        cout << "level(" << lineStr << "): " << strBST.getLevel(lineStr) <<
             ", ancestors(" << lineStr << "): " << strBST.getAncestors(lineStr) << endl;
    }

    cout << "\n** TEST CONTAINS **" << endl;
    srand(time(NULL));
    stringstream randStri;
    stringstream sstri;
    int strBSTSize = strBST.size();
    for (int i = 0; i <= strBSTSize; i++) {
        for(int z=0; z < 4; z++) {
            randStri << genRandom();
        }
        bool doesContain = strBST.contains(randStri.str());
        if (doesContain)
            cout << "contains(" << randStri.str() << "): true" << endl;
        else
            cout << "contains(" << randStri.str() << "): false" << endl;

        sstri << randStri.str() << " ";
        strBST.remove(randStri.str());
        randStri.str("");
    }

    cout << "\n** TEST REMOVE **" << endl;
    cout << "Removing in this order: " << sstri.str() << endl;
    // removed above

    string empty7;
    if (strBST.empty())
        empty7 = "true";
    else
        empty7 = "false";

    cout << "# of nodes: " << strBST.size() <<
         "\n# of leaves: " << strBST.getLeafCount() <<
         "\ntree height: " << strBST.getHeight() <<
         "\ntree empty? " << empty7 <<
         "\npre-order: " << strBST.getPreOrderTraversal() <<
         "\nin-order: " << strBST.getInOrderTraversal() <<
         "\npost-order: " << strBST.getPostOrderTraversal() << endl;

    string empty8;
    if (strBST.empty())
        empty8 = "true";
    else
        empty8 = "false";

    cout << "\n** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: " << sstri.str() << endl;

    string eachWord;
    while (getline(sstri, eachWord, ' ')) {
        strBST.insert(eachWord);
    }

    cout << "# of nodes: " << strBST.size() <<
         "\n# of leaves: " << strBST.getLeafCount() <<
         "\ntree height: " << strBST.getHeight() <<
         "\ntree empty? " << empty8 <<
         "\npre-order: " << strBST.getPreOrderTraversal() <<
         "\nin-order: " << strBST.getInOrderTraversal() <<
         "\npost-order: " << strBST.getPostOrderTraversal() << endl;

    return 0;
}
