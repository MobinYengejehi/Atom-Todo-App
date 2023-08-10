#include "Atom/Atom.h"
#include "Atom/AtomCssPropertiesMacros.h"

AtomCssStyleProperties CssContent() {
	return CssStyleSheet {
		Query(*:not(body)) {
			Margin = Css(0),
			Padding = Css(0),
			BoxSizing = Css(border-box)
		},

		Query(.lightmode) {
			CssProperty(--home-bg-color) = Css(#f3f3f3),
			CssProperty(--input-bg-color) = Css(#e3e3e3),
			CssProperty(--input-font-color) = Css(black),
			CssProperty(--todo-bg-color) = Css(white),
			CssProperty(--todo-font-color) = Css(black),
			CssProperty(--plus-logo-color) = Css(white),
			CssProperty(--header-color) = Css(rgb(255, 107, 0)),
			CssProperty(--github-fill) = Css(black),
			CssProperty(--github-hover-fill) = Css(white),
			CssProperty(--github-bg) = Css(black),
			CssProperty(--theme-check-color) = Css(var(--header-color)),
			CssProperty(--theme-check-hover-color) = Css(white),
			CssProperty(--theme-check-bg) = Css(var(--header-color)),
			CssProperty(--scroll-bar-thumb) = Css(rgb(19, 27, 39))
		},

		Query(.darkmode) {
			CssProperty(--home-bg-color) = Css(#353535),
			CssProperty(--input-bg-color) = Css(#484848),
			CssProperty(--input-font-color) = Css(white),
			CssProperty(--todo-bg-color) = Css(#636363),
			CssProperty(--todo-font-color) = Css(white),
			CssProperty(--plus-logo-color) = Css(#35383a),
			CssProperty(--header-color) = Css(hsl(9, 92%, 70%)),
			CssProperty(--github-fill) = Css(white),
			CssProperty(--github-hover-fill) = Css(#000000),
			CssProperty(--github-bg) = Css(white),
			CssProperty(--theme-check-bg) = Css(white),
			CssProperty(--theme-check-hover-color) = Css(var(--header-color)),
			CssProperty(--theme-check-color) = Css(white)
		},

		Query(body) {
			Height = Css(auto),
			Margin = Css(0),
			Width = Css(auto),
			Background = Css(var(--home-bg-color)),
			Color = Css(var(--home-font-color)),
			UserSelect = Css(none),
			CssProperty(--webkit-user-select) = Css(none),
			FontFamily = Css("Inter", sans-serif),
			Position = Css(relative),
			Display = Css(grid),
			AlignItems = Css(center)
		},

		Query(::-webkit-scrollbar) {
			Width = Css(5px),
			Background = Css(none)
		},

		Query(::-webkit-scrollbar-thumb) {
			Background = Css(grey),
			Opacity = Css(0.5),
			BorderRadius = Css(3px)
		},

		Query(#head) {
			Background = Css(var(--todo-bg-color)),
			Width = Css(100%),
			Position = Css(fixed),
			Top = Css(0),
			Left = Css(0),
			Right = Css(0),
			Display = Css(grid),
			GridTemplateColumns = Css(7rem 1fr repeat(2, 4rem)),
			BoxShadow = Css(0px -5px 20px 1px),
			ZIndex = Css(5)
		},

		$Media(only screen and (max-width: 756px)) {
			Query(#head) {
				GridTemplateColumns = Css(4rem 1fr repeat(2, 2.5rem))
			}
		},

		Query(#head #logo-icon) {
			Display = Css(flex),
			AlignItems = Css(center),
			JustifyContent = Css(center),
			Width = Css(100%),
			Height = Css(100%),
			Position = Css(relative)
		},

		Query(#head #logo-icon svg) {
			Width = Css(calc(3rem + 5px)),
			Height = Css(calc(3rem + 5px)),
			Padding = Css(5px),
			Background = Css(white),
			BorderRadius = Css(4px),
			Cursor = Css(pointer)
		},

		Query(#head #logo) {
			Padding = Css(1rem),
			Color = Css(var(--header-color)),
			FontFamily = Css("Patrick Hand", cursive),
			FontWeight = Css(700),
			FontSize = Css(1.9rem),
			Display = Css(flex),
			AlignItems = Css(center),
			Margin = Css(auto),
			Cursor = Css(pointer),
			TextDecoration = Css(none)
		},

		Query(#head #logo p) {
			PaddingLeft = Css(0.5rem),
			Color = Css(var(--header-color))
		},

		Query(#head #theme-check, #head #github) {
			Width = Css(100%),
			Height = Css(100%),
			Display = Css(flex),
			AlignItems = Css(center),
			JustifyContent = Css(center)
		},

		Query(#head #theme-check svg) {
			Fill = Css(var(--header-color)),
			Width = Css(calc(2rem + 5px)),
			Height = Css(calc(2rem + 5px)),
			Padding = Css(5px),
			BorderRadius = Css(4px),
			Cursor = Css(pointer),
			Fill = Css(var(--theme-check-color))
		},

		Query(#head #theme-check svg:hover) {
			Transition = Css(background 0.5s ease-in, fill 0.5s ease-in),
			Background = Css(var(--theme-check-bg)),
			Fill = Css(var(--theme-check-hover-color))
		},

		Query(#head #github svg) {
			Width = Css(calc(2rem + 5px)),
			Height = Css(calc(2rem + 5px)),
			Padding = Css(5px),
			BorderRadius = Css(4px),
			Cursor = Css(pointer),
			Fill = Css(var(--github-fill))
		},

		Query(#head #github svg:hover) {
			Transition = Css(background 0.5s ease-in, fill 0.5s ease-in),
			Background = Css(var(--github-bg)),
			Fill = Css(var(--github-hover-fill))
		},

		Query(#main-container) {
			Margin = Css(auto),
			Padding = Css(1rem),
			Width = Css(100%),
			MaxWidth = Css(700px)
		},

		Query(.svg-plus-logo) {
			Fill = Css(var(--plus-logo-color))
		},

		Query(button) {
			FontFamily = Css("Inter", sans-serif),
			Outline = Css(none),
			Border = Css(none),
			Background = Css(transparent),
			Cursor = Css(pointer)
		},

		Query(form) {
			Width = Css(100%),
			Display = Css(grid),
			GridTemplateColumns = Css(auto 33px),
			AlignItems = Css(center),
			GridColumnGap = Css(0.9rem),
			MarginTop = Css(5.5rem)
		},

		Query(form *) {
			Border = Css(none),
			Outline = Css(none)
		},

		Query(form input) {
			Background = Css(var(--input-bg-color)),
			Color = Css(var(--input-font-color)),
			BorderRadius = Css(13px),
			Padding = Css(10px 15px 10px 15px),
			FontSize = Css(0.95rem),
			FontFamily = Css("Inter", sans-serif),
			Width = Css(auto),
			GridColumnStart = Css(1),
			GridColumnEnd = Css(2)
		},

		Query(form button) {
			Background = Css(transparent),
			Height = Css(100%),
			Width = Css(35px)
		},

		Query(form button img) {
			Width = Css(120%),
			Height = Css(120%),
			Transform = Css(translate(-10%, -8%))
		},

		Query(#TODOs) {
			Width = Css(auto),
			Height = Css(auto),
			FontFamily = Css(500),
			MarginTop = Css(1.7rem),
			Overflow = Css(hidden)
		},

		Query(.todo) {
			Width = Css(100%),
			Display = Css(flex),
			AlignItems = Css(center),
			Background = Css(var(--todo-bg-color)),
			Color = Css(var(--todo-font-color)),
			BorderRadius = Css(7px),
			MarginTop = Css(5px),
			MarginBottom = Css(5px),
			Position = Css(relative),
			Transition = Css(opacity 0.5s ease-out),
			Overflow = Css(hidden),
			Animation = Css(slide-in 0.8s ease-in-out 1)
		},

		$KeyFrames(slide-in) {
			Query(from) {
				Transform = Css(translateX(-100%))
			},
			Query(to) {
				Transform = Css(translateX(0))
			}
		},

		Query(.todo-done) {
			Opacity = Css(50%)
		},

		Query(.todo-done::after) {
			Content = Css(""),
			Height = Css(2px),
			Width = Css(100%),
			Background = Css(#000),
			Position = Css(absolute),
			Top = Css(50%),
			Left = Css(0),
			Right = Css(0),
			Margin = Css(auto),
			Transform = Css(translateY(-50%)),
			Animation = Css(cross 1s ease-out 1)
		},

		$KeyFrames(cross) {
			Query(from) {
				Transform = Css(translateY(-50%) translateX(-100%))
			},
			Query(to) {
				Transform = Css(translateY(-50%) translateX(0%))
			}
		},

		Query(.todo-delete) {
			Transform = Css(translateX(0%)),
			Animation = Css(delete 0.8s ease-in-out 1)
		},

		$KeyFrames(delete) {
			Query(to) {
				Transform = Css(translateX(100%)),
				Opacity = Css(0.2)
			}
		},

		Query(.todo .content) {
			Padding = Css(10px 15px 10px 15px),
			Width = Css(85.5%),
			FontSize = Css(1.15rem)
		},

		Query(.todo .buttons) {
			Position = Css(absolute),
			Right = Css(5px),
			Margin = Css(auto),
			Transform = Css(translateY(7%))
		}
	};
}

AtomElement StyleSheet() {
	return AtomCreateStyleElement(CssContent());
}