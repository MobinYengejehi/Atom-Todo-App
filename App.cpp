#include "App.h"

#include "Atom/Atom.h"
#include "Atom/AtomMacros.h"
#include "Atom/AtomStyleMacros.h"

void ChangeTheme(ATOM_EVENT eventHandle) {
	AtomElement       body = AtomGetDocumentBodyElement();
	AtomClassManager& classManager = body.GetClassManager();

	classManager.ToggleClass("darkmode");
	classManager.ToggleClass("lightmode");

	ATOM_JS_VARIABLE localStorage = ATOM_JS_VARIABLE::global("localStorage");
	if (localStorage.isNull()) {
		return;
	}

	localStorage.call<void>("setItem", std::string("darkmode"), classManager.Contains("darkmode"));

	AtomElement themeCheck;
	body.QuerySelector("#theme-check", &themeCheck);

	themeCheck.Clear();

	if (classManager.Contains("darkmode")) {
		themeCheck += MoonImage() ATOM_SET_ELEMENT_REMOVABLE;
	}else if (classManager.Contains("lightmode")) {
		themeCheck += SunImage() ATOM_SET_ELEMENT_REMOVABLE;
	}
}

AtomElement MoonImage() {
	return SvgElement { Node "svg", SvgViewBox "0 0 512 512", SvgFill "white",
		SvgXmlNs "http://www.w3.org/2000/svg",
		Style {
			CssProperty(transform) = Css(scale(0.85))
		},
		OnClick ChangeTheme,
		SvgElement { Node "path",
			SvgD "M283.211 512c78.962 0 151.079-35.925 198.857-94.792 7.068-8.708-.639-21.43-11.562-19.35-124.203 23.654-238.262-71.576-238.262-196.954 0-72.222 38.662-138.635 101.498-174.394 9.686-5.512 7.25-20.197-3.756-22.23A258.156 258.156 0 0 0 283.211 0c-141.309 0-256 114.511-256 256 0 141.309 114.511 256 256 256z"
		}
	};
}

AtomElement SunImage() {
	return SvgElement { Node "svg", SvgWidth "24", SvgHeight "24", SvgViewBox "0 0 24 24",
		SvgXmlNs "http://www.w3.org/2000/svg",
		OnClick ChangeTheme,
		SvgElement { Node "path",
			SvgD "M6.76 4.84l-1.8-1.79-1.41 1.41 1.79 1.79 1.42-1.41zM4 10.5H1v2h3v-2zm9-9.95h-2V3.5h2V.55zm7.45 3.91l-1.41-1.41-1.79 1.79 1.41 1.41 1.79-1.79zm-3.21 13.7l1.79 1.8 1.41-1.41-1.8-1.79-1.4 1.4zM20 10.5v2h3v-2h-3zm-8-5c-3.31 0-6 2.69-6 6s2.69 6 6 6 6-2.69 6-6-2.69-6-6-6zm-1 16.95h2V19.5h-2v2.95zm-7.45-3.91l1.41 1.41 1.79-1.8-1.41-1.41-1.79 1.8z"
		}
	};
}

AtomElement ThemeCheck() {
	return Element { Node "div", Id "theme-check",
		SvgElement { Node "svg", SvgWidth "24", SvgHeight "24", SvgViewBox "0 0 24 24",
			SvgXmlNs "http://www.w3.org/2000/svg",
			OnClick ChangeTheme,
			SvgElement { Node "g",
				SvgElement { Node "path",
					SvgD "M6.76 4.84l-1.8-1.79-1.41 1.41 1.79 1.79 1.42-1.41zM4 10.5H1v2h3v-2zm9-9.95h-2V3.5h2V.55zm7.45 3.91l-1.41-1.41-1.79 1.79 1.41 1.41 1.79-1.79zm-3.21 13.7l1.79 1.8 1.41-1.41-1.8-1.79-1.4 1.4zM20 10.5v2h3v-2h-3zm-8-5c-3.31 0-6 2.69-6 6s2.69 6 6 6 6-2.69 6-6-2.69-6-6-6zm-1 16.95h2V19.5h-2v2.95zm-7.45-3.91l1.41 1.41 1.79-1.8-1.41-1.41-1.79 1.8z"
				}
			}
		}
	};
}

AtomElement Todo(const std::string& name) {
	if (name.empty()) {
		return NULL;
	}

	return Element { Node "div", Class "todo",
		Element { Node "p", Class "content",
			TextContent name
		},
		Element { Node "div", Class "buttons",
			Element { Node "button", Class "done", Style { CssProperty(margin-right) = Css(5px) },
				OnClick DoneTodo,
				Element { Node "img", Alt "done",
					Src "./assets/done.svg"
				}
			},
			Element { Node "button", Class "delete",
				OnClick DeleteTodo,
				Element { Node "img", Alt "delete",
					Src "./assets/delete.svg"
				}
			}
		}
	};
}

AtomElement Header() {
	return Element { Node "header", Id "head",
		Element { Node "div", Id "logo-icon",
			Element { Node "a",
				Href "https://github.com/anargya-anubhawa/todo-app/releases/download/v1.1.0-android/TODO_App_v1_1_0.apk",
		        Element { Node "img", Alt "TODO", Src "./assets/todo.png",
					Attribute { "width", "45vw" },
					Attribute { "height", "45vw" }					
				}
			}
		},
		Element { Node "div", Id "logo",
			Element { Node "p", TextContent "TO-DO APP" }
		},
		ThemeCheck(),
		Element { Node "a", Target "_blank", Id "github",
			Href "https://github.com/MobinYengejehi/Atom-HTML-CPP/tree/main",
			SvgElement { Node "svg", SvgViewBox "0 0 512 512",
				SvgElement { Node "path",
					SvgD "M256 32C132.3 32 32 134.9 32 261.7c0 101.5 64.2 187.5 153.2 217.9a17.56 17.56 0 003.8.4c8.3 0 11.5-6.1 11.5-11.4 0-5.5-.2-19.9-.3-39.1a102.4 102.4 0 01-22.6 2.7c-43.1 0-52.9-33.5-52.9-33.5-10.2-26.5-24.9-33.6-24.9-33.6-19.5-13.7-.1-14.1 1.4-14.1h.1c22.5 2 34.3 23.8 34.3 23.8 11.2 19.6 26.2 25.1 39.6 25.1a63 63 0 0025.6-6c2-14.8 7.8-24.9 14.2-30.7-49.7-5.8-102-25.5-102-113.5 0-25.1 8.7-45.6 23-61.6-2.3-5.8-10-29.2 2.2-60.8a18.64 18.64 0 015-.5c8.1 0 26.4 3.1 56.6 24.1a208.21 208.21 0 01112.2 0c30.2-21 48.5-24.1 56.6-24.1a18.64 18.64 0 015 .5c12.2 31.6 4.5 55 2.2 60.8 14.3 16.1 23 36.6 23 61.6 0 88.2-52.4 107.6-102.3 113.3 8 7.1 15.2 21.1 15.2 42.5 0 30.7-.3 55.5-.3 63 0 5.4 3.1 11.5 11.4 11.5a19.35 19.35 0 004-.4C415.9 449.2 480 363.1 480 261.7 480 134.9 379.7 32 256 32z"
				}
			}
		}
	};
}

AtomElement Form() {
	return Element { Node "form", Id "input-container",
		OnSubmit FormSubmit,
		Element { Node "input",
			Name "input",
			Type "text",
			Id "input",
			PlaceHolder "Enter Here ...",
			AutoComplete "off",
			AutoCapitalize "on"
		},
		Element { Node "button", Type "submit",
			SvgElement { Node "svg", SvgWidth "33", SvgHeight "33", SvgViewBox "0 0 33 33", SvgFill "none",
				SvgXmlNs "http://www.w3.org/2000/svg",
				SvgElement { Node "circle", SvgFill "#FFCF73",
					Attribute { "cx", "16.5" },
					Attribute { "cy", "16.5" },
					Attribute { "r", "16.5" }
				},
				SvgElement { Node "path", Class "svg-plus-logo", SvgFill "#353535",
					SvgD "M24.0429 14.6437H18.3857V9.07499C18.3857 8.39166 17.8227 7.83749 17.1286 7.83749H15.8714C15.1772 7.83749 14.6143 8.39166 14.6143 9.07499V14.6437H8.95714C8.26296 14.6437 7.7 15.1979 7.7 15.8812V17.1187C7.7 17.8021 8.26296 18.3562 8.95714 18.3562H14.6143V23.925C14.6143 24.6083 15.1772 25.1625 15.8714 25.1625H17.1286C17.8227 25.1625 18.3857 24.6083 18.3857 23.925V18.3562H24.0429C24.737 18.3562 25.3 17.8021 25.3 17.1187V15.8812C25.3 15.1979 24.737 14.6437 24.0429 14.6437Z"
				}
			}
		}
	};
}

AtomElement MainContainer() {
	return Element { Node "section", Id "main-container",
		Header(),
		Form(),
		Element { Node "section", Id "TODOs" }
	};
}

AtomElement App() {
	return Element { Node "div",
		MainContainer(),
		Element { Node "div",
			Style {
				CssProperty(position) = Css(relative),
				CssProperty(width) = Css(87vw),
				CssProperty(height) = Css(79vw)
			},
			Element { Node "div",
				Style {
					CssProperty(margin-left) = Css(3px),
					CssProperty(position) = Css(absolute),
					CssProperty(bottom) = Css(1vw),
					CssProperty(font-family) = Css(Patrick Hand)
				},
				Element { Node "p", Align "bottom",
					InnerContent "Report bug",
					Element { Node "a",
						Style {
							CssProperty(margin-left) = Css(5px)
						},
						Href "https://github.com/MobinYengejehi/Atom-HTML-CPP/tree/main",
						InnerContent "here"
					},
					BreakLine,
					InnerContent "Hint: Click the logo on the top left"
				}
			}
		}
	};
}