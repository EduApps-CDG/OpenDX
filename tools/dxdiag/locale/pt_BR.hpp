#pragma once
#include <types/Translation.hpp>
#include "en_US.hpp"

/**
 * TODO Completar
 */
Translation_t Translation_ptBR() {
	Translation_t r = Translation_enUS();

	//Common texts
	r.yes = (char*) "Sim";

	return r;
}
