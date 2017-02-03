/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ============
#include "ScriptEngine.h"
#include <memory>
//=======================

class GameObject;
class asIScriptObject;
class asIScriptFunction;

// Allows creation of a script instance and execution of it's class functions.
class ScriptInstance
{
public:
	ScriptInstance();
	~ScriptInstance();

	bool Instantiate(const std::string& path, GameObject* gameObject, ScriptEngine* scriptEngine);
	bool IsInstantiated();
	std::string GetScriptPath();

	void ExecuteStart();
	void ExecuteUpdate();

private:
	bool CreateScriptObject();

	std::string m_scriptPath;
	std::string m_className;
	std::string m_constructorDeclaration;
	std::string m_moduleName;
	GameObject* m_gameObject;
	std::shared_ptr<Module> m_module;
	asIScriptObject* m_scriptObject;
	asIScriptFunction* m_constructorFunction;
	asIScriptFunction* m_startFunction;
	asIScriptFunction* m_updateFunction;
	bool m_isInstantiated;
	ScriptEngine* m_scriptEngine;
};
