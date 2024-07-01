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

LinkedList::Node::Node(const std::string varname, TokenType type) : varname(varname), type(type), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}

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
    for (int i = 0; i < amount; i++)
    {
        temp->type = type;
        temp = temp->next;
    }
}

void LinkedList::addNode(const std::string &varname, TokenType type)
{
    Node *newNode = new Node(varname, type);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

TokenType LinkedList::search(const std::string &varname)
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
    return ERROR;
}

void LinkedList::printList()
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
    head = nullptr;
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