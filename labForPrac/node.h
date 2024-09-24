#pragma once

#include "user.h"

struct Node {
	User user;
	Node* next;
	Node* prev;
};

void InitList(Node* node, User user);
void AddUser(Node*& head, User user);
void addElBegin(Node*& head, User user);
void removeHead(Node*& head);;
void removeLastEl(Node*& head);
void removeHead(Node*& head);
void removeList(Node*& head);
bool emptyList(Node* list);
void printList(Node* head);
