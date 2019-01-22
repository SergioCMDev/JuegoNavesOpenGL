#pragma once
#ifndef CONSTANTS_H     
#define  CONSTANTS_H

#include<string>

class Constants
{
public:
	static constexpr const  char* pathProyecto = "../tests/PracticaFinal/";
	static constexpr const  char* pathToPlayerModel = "../assets/obj/Freighter/Freigther_BI_Export.obj";
	static const uint32_t MaximoObjectosTransferencia = 10;
	static const uint32_t TIPO_PLAYER = 1;
	static const uint32_t TIPO_METEOR = 2;
	static const uint32_t TIPO_ENEMIGO = 3;
	static const uint32_t TIPO_MISIL = 4;
	static const int MAX_POSITION_Y = 20;
	static const int MIN_POSITION_Y = -20;
	static const int MAX_POSITION_X = 15;
	static const int MIN_POSITION_X = -15;
};
#endif