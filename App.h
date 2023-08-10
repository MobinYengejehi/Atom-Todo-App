#pragma once

#ifndef APP_HEADER
#define APP_HEADER

#include "Atom/AtomElement.h"

#include <vector>
#include <string>

typedef std::vector<std::string> TodoList;

void GetTodoList(TodoList* list);
void SaveTodoList(TodoList* list);

void DoneTodo(ATOM_EVENT eventHandle);
void DeleteTodo(ATOM_EVENT eventHandle);

void FormSubmit(ATOM_EVENT eventHandle);

AtomElement StyleSheet();

AtomElement MoonImage();
AtomElement SunImage();

AtomElement Todo(const std::string& name);

AtomElement App();

#endif