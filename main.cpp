#include <iostream>

#include "Atom/Atom.h"

#include "App.h"

void GetTodoList(TodoList* list) {
	if (!list) {
		return;
	}

	ATOM_JS_VARIABLE global = ATOM_JS_VARIABLE::global(NULL);
	ATOM_JS_VARIABLE localStorage = global["localStorage"];
	if (localStorage.isNull()) {
		return;
	}

	ATOM_JS_VARIABLE data = localStorage.call<ATOM_JS_VARIABLE>("getItem", std::string("todoList"));
	if (!data.isString()) {
		return;
	}

	std::string listJsonData = data ATOM_AS_STRING;

	if (listJsonData.empty()) {
		return;
	}

	ATOM_JS_VARIABLE json = global["JSON"];

	ATOM_JS_VARIABLE arrayList = json.call<ATOM_JS_VARIABLE>("parse", listJsonData);

	size_t length = arrayList["length"] ATOM_AS_ULONG;

	for (size_t i = 0; i < length; i++) {
		list->push_back(arrayList[i] ATOM_AS_STRING);
	}
}

void SaveTodoList(TodoList* list) {
	if (!list) {
		return;
	}

	ATOM_JS_VARIABLE global = ATOM_JS_VARIABLE::global(NULL);
	ATOM_JS_VARIABLE localStorage = global["localStorage"];
	if (localStorage.isNull()) {
		return;
	}

	if (list->empty()) {
		localStorage.call<void>("setItem", std::string("todoList"), std::string("[]"));
	}

	ATOM_JS_VARIABLE json = global["JSON"];

	ATOM_JS_VARIABLE arrayList = ATOM_JS_VARIABLE::array<std::string>(*list);

	std::string listJsonData = json.call<std::string>("stringify", arrayList);

	localStorage.call<void>("setItem", std::string("todoList"), listJsonData);
}

void DoneTodo(ATOM_EVENT eventHandle) {
	ATOM_JS_VARIABLE e = ATOM_EVENT_VARIABLE(eventHandle);

	ATOM_JS_VARIABLE todoElementObject = (
		e
		["target"]
		["parentNode"]
		["parentNode"]
		["parentNode"]
	);

	if (todoElementObject.isNull()) {
		return;
	}

	ATOM_JS_VARIABLE global = ATOM_JS_VARIABLE::global(NULL);

	AtomElement       todoElement = AtomGetElementFromJS(todoElementObject);
	AtomClassManager& classManager = todoElement.GetClassManager();

	classManager.ToggleClass("todo-done");

	AtomElement contentHolder;
	todoElement.QuerySelector(".content", &contentHolder);

	std::string content = contentHolder.GetProperty("textContent");

	TodoList list;
	GetTodoList(&list);

	const size_t length = list.size();

	int index = -1;

	for (int i = 0; i < length; i++) {
		if (list[i] == content || list[i] == std::string("~~~") + content) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		if (classManager.Contains("todo-done")) {
			list[index] = std::string("~~~") + content;
		}else{
			list[index] = content;
		}
	}

	SaveTodoList(&list);
}

void DeleteTodo(ATOM_EVENT eventHandle) {
	ATOM_JS_VARIABLE e = ATOM_EVENT_VARIABLE(eventHandle);

	ATOM_JS_VARIABLE todoElementObject = (
		e
		["target"]
		["parentNode"]
		["parentNode"]
		["parentNode"]
	);

	if (todoElementObject.isNull()) {
		return;
	}

	ATOM_JS_VARIABLE global = ATOM_JS_VARIABLE::global(NULL);

	AtomElement       todoElement = AtomGetElementFromJS(todoElementObject);
	AtomClassManager& classManager = todoElement.GetClassManager();

	classManager.AddClass("todo-delete");

	AtomElement contentHolder;
	todoElement.QuerySelector(".content", &contentHolder);

	std::string content = contentHolder.GetProperty("textContent");

	TodoList list;
	GetTodoList(&list);
	
	const size_t length = list.size();

	int index = -1;

	for (int i = 0; i < length; i++) {
		if (list[i] == content || list[i] == std::string("~~~") + content) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		list.erase(list.begin() + index);
		SaveTodoList(&list);
	}

	ATOM_DIRECT_ASM({
		const todoElement = atom_get_element_by_reference($0);

		if (!todoElement) {
			return;
		}

		setTimeout(function() {
			todoElement.remove();
		}, 800);
	}, todoElement.GetHandle());
}

void AddTodoElement(const std::string& content) {
	if (content.empty()) {
		return;
	}
	
	AtomElement todo = Todo(content.starts_with("~~~") ? content.substr(3) : content) ATOM_SET_ELEMENT_REMOVABLE;

	ATOM_DIRECT_ASM({
		const Todos = document.querySelector("#TODOs");
		Todos.insertAdjacentElement("afterbegin", atom_get_element_by_reference($0));
	}, todo.GetHandle());

	if (content.starts_with("~~~")) {
		todo.GetClassManager().ToggleClass("todo-done");
	}
}

void FormSubmit(ATOM_EVENT eventHandle) {
	ATOM_JS_VARIABLE e = ATOM_EVENT_VARIABLE(eventHandle);
	e.call<void>("preventDefault");

	AtomElement body = AtomGetDocumentBodyElement();

	AtomElement input;
	body.QuerySelector("#input", &input);

	if (!input) {
		return;
	}

	std::string content = TrimString(input.GetProperty("value"));
	if (content.empty()) {
		return;
	}

	ATOM_DIRECT_ASM({ atom_get_element_by_reference($0).value = "";}, input.GetHandle());

	TodoList list;
	GetTodoList(&list);

	if (std::find(list.begin(), list.end(), content) != list.end()) {
		return;
	}

	if (std::find(list.begin(), list.end(), std::string("~~~") + content) != list.end()) {
		return;
	}

	AddTodoElement(content);
	
	list.push_back(content);
	SaveTodoList(&list);
}

void Init() {
	AtomElement body = AtomGetDocumentBodyElement();
	AtomClassManager& classManager = body.GetClassManager();

	ATOM_JS_VARIABLE global = ATOM_JS_VARIABLE::global();
	ATOM_JS_VARIABLE localStorage = global["localStorage"];

	std::string darkMode = "false";

	if (!localStorage.isNull()) {
		ATOM_JS_VARIABLE mode = localStorage.call<ATOM_JS_VARIABLE>("getItem", std::string("darkmode"));
		if (!mode.isNull()) {
			darkMode = mode ATOM_AS_STRING;
		}
	}

	AtomElement themeCheck;
	body.QuerySelector("#theme-check", &themeCheck);

	themeCheck.Clear();

	if (darkMode == "true") {
		classManager -= "lightmode";
		classManager += "darkmode";
		themeCheck += MoonImage() ATOM_SET_ELEMENT_REMOVABLE;
	}else{
		classManager -= "darkmode";
		classManager += "lightmode";
		themeCheck += SunImage() ATOM_SET_ELEMENT_REMOVABLE;
	}

	AtomElement input;
	body.QuerySelector("#input", &input);

	TodoList list;
	GetTodoList(&list);

	if (list.empty()) {
		list.push_back("Start your to-do list");
		SaveTodoList(&list);
	}

	for (const std::string& todo : list) {
		AddTodoElement(todo);
	}
}

int main() {
	atom_application_init();

	// Attach `CssStyleSheet` to document head
	AtomGetDocumentHeadElement() += StyleSheet();

	// Attach `App Component` to document body
	AtomGetDocumentBodyElement() += App() ATOM_SET_ELEMENT_REMOVABLE;
	
	Init();

	// Application main loop to keep our runtime alive
	while (true) atom_sleep(10000);

	atom_exit(NULL);

	return NULL;
}