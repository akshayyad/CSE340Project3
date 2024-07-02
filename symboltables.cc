#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

#include "symboltables.h"
#include "lexer.h"

// Node constructor
LinkedList::Node::Node(const std::string &varname, TokenType type)
    : varname(varname), type(type), binNo(0), next(nullptr), prev(nullptr) {}

// DoublyLinkedList constructor
LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

// DoublyLinkedList destructor
LinkedList::~LinkedList()
{
    clear();
}

LinkedList::Node *LinkedList::getHead() const
{
    return head;
}

void LinkedList::assignTypes(int amount, TokenType type)
{
    Node *temp = head;
    for (int i = 0; i < amount & temp != nullptr; i++)
    {
        temp->type = type;
        temp = temp->next;
    }
}

void LinkedList::addNode(const std::string &varname, TokenType type, int binNo)
{
    Node *newNode = new Node(varname, type);
    newNode->binNo = binNo;
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

int LinkedList::search(const std::string &varname)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->varname == varname)
        {
            return temp->type;
        }
        temp = temp->next;
    }
    return -1;
}

void LinkedList::printList() const
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->varname << " " << temp->type << std::endl;
        temp = temp->next;
    }
    std::cout << std::endl;
}

void LinkedList::clear()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

Assignments::Assignments() : declarations() {}
Assignments::~Assignments() {}

void Assignments::addAssignment(const std::string &data)
{
    declarations.push_back(data);
}

void Assignments::printAssignments()
{
    for (int i = 0; i < declarations.size(); i++)
    {
        std::cout << declarations[i] << std::endl;
    }
}

void Assignments::setImplicitVar(const std::string name)
{
    implicitVar = name;
}

void Assignments::addImplicitVar(const std::string name)
{
    implicitvars.push_back(name);
}