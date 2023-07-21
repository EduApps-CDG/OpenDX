#pragma once

typedef struct {
	//Common texts
	char* yes;
	char* no;
	char* not_available;
	char* enabled;

	//Tab names
	char* tab_system;
	char* tab_display;
	char* tab_sound;
	char* tab_input;

	//Buttons
	char* btn_help;
	char* btn_next;
	char* btn_save;
	char* btn_exit;

	//Tab System
	char* system_description; //This tool reports [...]
	char* system_info_label; //Section System Info
	char* system_info_currentDate;
	char* system_info_pcName;
	char* system_info_os;
	char* system_info_language;
	char* system_info_manufacturer;
	char* system_info_model;
	char* system_info_bios;
	char* system_info_processor;
	char* system_info_memory;
	char* system_info_pageFile;
	char* system_info_directxVersion;
	char* system_info_opendxVersion; //exclusive :)

	//Tab Display X
	char* display_device_label; // section Device
	char* display_device_manufacturer;
	char* display_device_chipType;
	char* display_device_dacType;
	char* display_device_type;
	char* display_device_mem;
	char* display_device_videoMem;
	char* display_device_sharedMem;
	char* display_device_currDisplayMode;
	char* display_device_monitor;
	char* display_driver_label; //section Drivers
	char* display_driver_mainDriver;
	char* display_driver_version;
	char* display_driver_date;
	char* display_driver_whqlLogo;
	char* display_driver_d3dDdi;
	char* display_driver_featureLevels;
	char* display_driver_model;
	char* display_features_label; //section DirecX Features
	char* display_features_ddAccel;
	char* display_features_d3dAccel;
	char* display_features_agpAccel;
	char* display_notes_label; //section Notes

	//Tab Sound
	char* sound_device_label; //section Device
	char* sound_device_name;
	char* sound_device_hardwareId;
	char* sound_device_manufacturerId;
	char* sound_device_productId;
	char* sound_device_type;
	char* sound_device_default;
	char* sound_driver_label; //section Drivers
	char* sound_driver_name;
	char* sound_driver_version;
	char* sound_driver_date;
	char* sound_driver_whqlLogo;
	char* sound_driver_otherFiles;
	char* sound_driver_provider;
	char* sound_notes_label; //section Notes
} Translation_t;
