#pragma once
#include <types/Translation.hpp>

/**
 * TODO Complete with @see /include/types/Translation.hpp
 */
Translation_t Translation_enUS() {
	Translation_t r;

	//Common texts
	r.yes = (char*) "Sí";
	r.no = (char*) "No";
	r.not_available = (char*) "No disponible";
	r.enabled = (char*) "Habilitado";

	//Tab names
	r.tab_system = (char*) "Sistema";
	r.tab_display = (char*) "Pantalla";
	r.tab_sound = (char*) "Sonido";
	r.tab_input = (char*) "Entrada";

	//Buttons
	r.btn_help = (char*) "Ayuda";
	r.btn_next = (char*) "Siguiente";
	r.btn_save = (char*) "Guardar";
	r.btn_exit = (char*) "Salir";

	//Tab System
	r.system_description = (char*) "Esta herramienta informa de información detallada sobre los componentes y controladores OpenDX instalados en su sistema.\n\nSi sabe qué área está causando el problema, haga clic en la pestaña correspondiente arriba. De lo contrario, puede usar el botón \"Página siguiente\" a continuación para visitar cada página en secuencia.";
	r.system_info_label = (char*) "Información del sistema";
	r.system_info_currentDate = (char*) "Fecha y hora actuales";
	r.system_info_pcName = (char*) "Nombre del ordenador";
	r.system_info_os = (char*) "Sistema operativo";
	r.system_info_language = (char*) "Idioma";
	r.system_info_manufacturer = (char*) "Fabricante del sistema";
	r.system_info_model = (char*) "Modelo del sistema";
	r.system_info_bios = (char*) "BIOS";
	r.system_info_processor = (char*) "Procesador";
	r.system_info_memory = (char*) "Memoria";
	r.system_info_pageFile = (char*) "Archivo de paginación";
	r.system_info_directxVersion = (char*) "Versión de DirectX";
	r.system_info_opendxVersion = (char*) "Versión de OpenDX";

	return r;
}
