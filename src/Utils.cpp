#include "Utils.h"
#include "Shader.h"
#include "Constants.h"

string Utils::GetFinalPath(const string pathInicial, const string  variablePath)
{  
	string finalPath = pathInicial + variablePath;
	cout << finalPath.c_str() << endl;
	return finalPath;
};

Shader Utils::GetFullShader(const string pathVertex, const string pathFragment) {
	string vertexpathStr = Utils::GetFinalPath(Constants::pathProyecto, pathVertex);
	const char* vertexpath = vertexpathStr.c_str();

	string fragmentPathString = Utils::GetFinalPath(Constants::pathProyecto, pathFragment);
	const char* fragmentPath1 = fragmentPathString.c_str();

	return Shader(vertexpath, fragmentPath1);
};

Shader& Utils::GetFullShader2(const string pathVertex, const string pathFragment) {
	string vertexpathStr = Utils::GetFinalPath(Constants::pathProyecto, pathVertex);
	const char* vertexpath = vertexpathStr.c_str();

	string fragmentPathString = Utils::GetFinalPath(Constants::pathProyecto, pathFragment);
	const char* fragmentPath1 = fragmentPathString.c_str();

	return Shader(vertexpath, fragmentPath1);
};
