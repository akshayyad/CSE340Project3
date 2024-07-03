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
LinkedList::Node::Node(const std::string &varname, int type)
    : varname(varname), type(type), binNo(0), next(nullptr), prev(nullptr), printed(0) {}

// DoublyLinkedList constructor
LinkedList::LinkedList() : head(nullptr), tail(nullptr), global(5) {}

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
    Node *temp = tail;
    for (int i = 0; i < amount && temp != nullptr; i++)
    {
        temp->type = type;
        temp = temp->prev;
    }
}

void LinkedList::addNode(const std::string &varname, int type, int group)
{
    Node *newNode = new Node(varname, type);
    newNode->group = group;
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
    if (temp == nullptr)
    {
        addNode(varname, global, -2);
        global++;
        return (5);
    }
    else
    {
        while (temp != nullptr)
        {
            if (temp->varname == varname)
            {
                return temp->type;
            }
            temp = temp->next;
        }
        addNode(varname, global, global);
        global++;
        return global - 1;
    }
    return -1;
}

void LinkedList::rearrangeTypes(int oldType, int newType)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->type == oldType)
        {
            temp->type = newType;
        }
        temp = temp->next;
    }
}

std::string LinkedList::intToType(int type)
{
    switch (type)
    {
    case 1:
        return "int";
    case 2:
        return "real";
    case 3:
        return "bool";
    default:
        return "?";
    }
}

/*void LinkedList::outputVars()
{
    Node *temp = head;
    // First Print out the Known Vars
    while (temp != nullptr)
    {
        if (temp->type >= 1 && temp->type <= 3)
        {
            // int type = temp->type;
            // std::string currentTypeName = intToType(type);
            //  x: int #
            std::cout << temp->varname << ": " << intToType(temp->type) << " #"
                      << std::endl;
        }
        temp = temp->next;
    }
    // Then Print out the Unknown Vars
    // x5, y5: ? #
    for (int i = 5; i < global; i++)
    {
        // printf("Group %d:\n", i);
        std::string currentGroup = "";
        temp = head;
        while (temp != nullptr)
        {
            // printf("I am called with Group: %d\n", i);
            if (temp->type == i)
            {
                if (currentGroup == "")
                {
                    currentGroup = temp->varname;
                }
                else
                {
                    currentGroup += ", " + temp->varname;
                }
            }
            temp = temp->next;
        }
        if (currentGroup != "")
        {
            std::cout << currentGroup << ": ? #" << std::endl;
        }
    }
} */

/**/ void LinkedList::outputVars()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->type > 4 && temp->printed == 0)
        {
            int currentGroup = temp->type;
            // std::string currentOutput = "";
            std::string currentOutput = temp->varname;
            temp->printed = 1;
            temp = temp->next;
            while (temp != nullptr)
            {
                if (temp->type == currentGroup)
                {
                    if (currentOutput == "")
                    {
                        currentOutput = temp->varname;
                        temp->printed = 1;
                    }
                    else
                    {
                        currentOutput += ", " + temp->varname;
                        temp->printed = 1;
                    }
                }
                temp = temp->next;
            }
            if (currentOutput != "")
            {
                std::cout << currentOutput << ": ? #" << std::endl;
            }
            temp = head;
        }
        else if (temp->type <= 3 && temp->printed == 0)
        {
            std::string type = intToType(temp->type);
            int currentType = temp->type;
            std::string currentOutput = temp->varname + ": " + type + " #";
            std::cout << currentOutput << std::endl;
            temp->printed = 1;
            while (temp->next != nullptr && temp->next->type == currentType)
            {
                temp = temp->next;
                int currentType = temp->type;
                std::string currentOutput = temp->varname + ": " + type + " #";
                std::cout << currentOutput << std::endl;
                temp->printed = 1;
            }
        }
        else
        {
            temp = temp->next;
        }
    }
} /**/

void LinkedList::printList() const
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->varname << " " << temp->type << /*" " << temp->group <<*/ std::endl;
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

std::string Assignments::removeLastImplicitVar()
{
    std::string temp = implicitvars.back();
    implicitvars.pop_back();
    return temp;
}