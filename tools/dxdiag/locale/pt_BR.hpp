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
	r.no = (char*) "Não";
	r.not_available = (char*) "Indisponível";
	r.enabled = (char*) "Habilitado";

	//Tab names
	r.tab_system = (char*) "Sistema";
	r.tab_display = (char*) "Exibição";
	r.tab_sound = (char*) "Som";
	r.tab_input = (char*) "Entrada";

	//Buttons
	r.btn_help = (char*) "Ajuda";
	r.btn_next = (char*) "Próximo";
	r.btn_save = (char*) "Salvar";
	r.btn_exit = (char*) "Sair";

	return r;
}
