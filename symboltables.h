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
private:
    struct Node
    {
        std::string varname;
        int type;
        int binNo;
        Node *next;
        Node *prev;
        int group;

        Node(const std::string &varname, int type);
    };

    Node *head;
    Node *tail;

public:
    LinkedList();
    ~LinkedList();

    Node *getHead() const;
    void assignTypes(int amount, TokenType type);
    void addNode(const std::string &varname, int type, int group);
    int search(const std::string &varname);
    void printList() const;
    void clear();
};

class Assignments
{
public:
    Assignments();
    ~Assignments();
    void addAssignment(const std::string &data);
    void printAssignments();
    void setImplicitVar(const std::string name);

    void addImplicitVar(const std::string name);
    std::string removeLastImplicitVar();

private:
    std::vector<std::string> declarations;
    std::string implicitVar;
    std::vector<std::string> implicitvars;
};

#endif // LINKEDLIST_H