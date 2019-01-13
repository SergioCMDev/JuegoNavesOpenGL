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

};
#endif