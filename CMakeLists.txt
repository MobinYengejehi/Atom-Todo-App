cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SimpleTodoAppAtom")

add_executable (SimpleTodoAppAtom   "Atom/Atom.h" "Atom/AtomClassManager.cpp" "Atom/AtomClassManager.h" "Atom/AtomCssPropertiesMacros.h" "Atom/AtomElement.cpp" "Atom/AtomElement.h" "Atom/AtomElementOptions.cpp" "Atom/AtomElementOptions.h" "Atom/AtomJSDefinitions.cpp" "Atom/AtomJSDefinitions.h" "Atom/AtomMacros.h" "Atom/AtomStyleMacros.h" "Atom/AtomStyleManager.cpp" "Atom/AtomStyleManager.h" "main.cpp" "App.h" "App.cpp" "StyleSheet.cpp" "Atom/AtomUtils.h" "Atom/AtomUtils.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleTodoAppAtom PROPERTY CXX_STANDARD 20)
endif()
