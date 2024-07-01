#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

#include "lexer.h"
#include "inputbuf.h"

class LinkedList
{
public:
    struct Node
    {
        std::string varname;
        TokenType type;
        Node *next;

        Node(const std::string varname, TokenType type);
    };

    LinkedList();
    ~LinkedList();

    Node *getHead() const;

    void assignTypes(int amount, TokenType type);

    void addNode(const std::string &varname, TokenType type);

    TokenType search(const std::string &varname);

    void printList();

    void remove(const std::string &varname);

private:
    Node *head;
    void clear();
};

class Assignments
{
public:
    Assignments();
    ~Assignments();
    void addAssignment(const std::string &data);
    void printAssignments();

private:
    std::vector<std::string> declarations;
};

#endif // LINKEDLIST_H