#pragma once

#ifndef UTILS_H
#define UTILS_H
#include<iostream>
#include "string.h"
#include "Shader.h"


class Utils {

public:
	static std::string GetFinalPath(const std::string pathInicial, const std::string pathFinal);
	static Shader GetFullShader(const std::string pathVertex, const std::string pathFragment);
};
#endif