#pragma once
#include <types/Translation.hpp>

/**
 * TODO Complete with project://include/types/Translation.hpp
 */
Translation_t Translation_enUS() {
	Translation_t r;

	//Common texts
	r.yes = (char*) "Yes";
	r.no = (char*) "No";
	r.not_available = (char*) "Not Available";
	r.enabled = (char*) "Enabled";

	//Tab names
	r.tab_system = (char*) "System";
	r.tab_display = (char*) "Display";
	r.tab_sound = (char*) "Sound";
	r.tab_input = (char*) "Input";

	//Buttons
	r.btn_help = (char*) "Help";
	r.btn_next = (char*) "Next";
	r.btn_save = (char*) "Save";
	r.btn_exit = (char*) "Exit";

	//Tab System
	r.system_description = (char*) "This tool reports detailed information about the OpenDX components and drivers installed on your system.\n\nIf you know what area is causing the problem, click on the apropriate tab above. Otherwise, you can yse the \"Next Page\" button below to visit each page in sequence.";
	r.system_info_label = (char*) "System Information";
	r.system_info_currentDate = (char*) "Current Date/Time";
	r.system_info_pcName = (char*) "Computer Name";
	r.system_info_os = (char*) "Operating System";
	r.system_info_language = (char*) "Language";
	r.system_info_manufacturer = (char*) "System Manufacturer";
	r.system_info_model = (char*) "System Model";
	r.system_info_bios = (char*) "BIOS";
	r.system_info_processor = (char*) "Processor";
	r.system_info_memory = (char*) "Memory";
	r.system_info_pageFile = (char*) "Page file";
	r.system_info_directxVersion = (char*) "DirectX Version";
	r.system_info_opendxVersion = (char*) "OpenDX Version";

	return r;
}
