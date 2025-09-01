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

	// Tab Display X

	r.display_device_label = (char*) "Device";
	r.display_device_manufacturer = (char*)"Manufacturer";
	r.display_device_chipType = (char*)"Chip Type";
	r.display_device_dacType = (char*)"DAC Type";
	r.display_device_type = (char*)"Device Type";
	r.display_device_mem = (char*)"Total Memory";
	r.display_device_videoMem = (char*)"Video Memory";
	r.display_device_sharedMem = (char*)"Shared Memory";
	r.display_device_currDisplayMode = (char*)"Current Display Mode";
	r.display_device_monitor = (char*)"Monitor";
	r.display_driver_label = (char*)"Drivers";
	r.display_driver_mainDriver = (char*)"Main Driver";
	r.display_driver_version = (char*)"Version";
	r.display_driver_date = (char*)"Date";
	r.display_driver_whqlLogo = (char*)"WHQL Logo";
	r.display_driver_d3dDdi = (char*)"Direct3D DDI";
	r.display_driver_featureLevels = (char*)"Feature";
	r.display_driver_model = (char*)"Model";
	r.display_features_ddAccel = (char*) "DD Accel";
	r.display_features_d3dAccel = (char*)"D3D Accel";
	r.display_features_agpAccel = (char*)"AGP Accel";
	r.display_notes_label = (char*)"Notes";

	// Tab Sound

	r.sound_device_label = (char*) "Device";
	r.sound_device_name = (char*) "Device Name";
	r.sound_device_hardwareId = (char*)"Hardware ID";
	r.sound_device_manufacturerId = (char*)"Manufacturer ID";
	r.sound_device_productId = (char*)"Product ID";
	r.sound_device_type = (char*)"Type";
	r.sound_device_default = (char*)"Default Device";
	r.sound_driver_label = (char*)"Drivers";
	r.sound_driver_name = (char*)"Name";
	r.sound_driver_version = (char*)"Version";
	r.sound_driver_date = (char*)"Date";
	r.sound_driver_whqlLogo = (char*)"WHQL Logo";
	r.sound_driver_otherFiles = (char*)"Other Files";
	r.sound_driver_provider = (char*)"Provider";
	r.sound_notes_label = (char*)"Notes";



	return r;
}
