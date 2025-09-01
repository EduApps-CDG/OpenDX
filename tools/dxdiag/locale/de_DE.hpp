#pragma once
#include <types/Translation.hpp>
#include "en_US.hpp"

/**
 * TODO Complete with project://include/types/Translation.hpp
 */
Translation_t Translation_deDE() {
    Translation_t r;

    //Common texts
    r.yes = (char*) "Ja";
    r.no = (char*) "Nein";
    r.not_available = (char*) "Nicht verfügbar";
    r.enabled = (char*) "An";

    //Tab names
    r.tab_system = (char*) "System";
	r.tab_display = (char*) "Anzeige";
	r.tab_sound = (char*) "Sound";
	r.tab_input = (char*) "Eingabe";

    //Buttons
    r.btn_help = (char*) "Hilfe";
	r.btn_next = (char*) "Nächste Seite";
	r.btn_save = (char*) "Alle Informationen speichern...";
	r.btn_exit = (char*) "Beenden";

    //Tab system
    r.system_description = (char*) "Dieses Programm gibt detaillierte Informationen über die DirectX-Komponenten und -Treiber dieses Computers an.\n\nWählen Sie die entsprechende Registerkarte oben, wenn Sie den Bereich des Problems bereits kennen. Klicken Sie andernfalls auf \"Nächste Seite\", um alle Seiten nacheinander zu durchsuchen.";
	r.system_info_label = (char*) "Systeminformation";
	r.system_info_currentDate = (char*) "Aktuelles Datum/Zeit";
	r.system_info_pcName = (char*) "Computername";
	r.system_info_os = (char*) "Betriebssystem";
	r.system_info_language = (char*) "Sprache";
	r.system_info_manufacturer = (char*) "Systemhersteller";
	r.system_info_model = (char*) "Systemmodell";
	r.system_info_bios = (char*) "BIOS";
	r.system_info_processor = (char*) "Prozessor";
	r.system_info_memory = (char*) "Speicher";
	r.system_info_pageFile = (char*) "Auslagerungsdatei";
	r.system_info_directxVersion = (char*) "DirectX-Version";
	r.system_info_opendxVersion = (char*) "OpenDX-Version";

    //Tab Display
    r.display_device_label = (char*) "Gerät";
	r.display_device_manufacturer = (char*) "Hersteller";
	r.display_device_chipType = (char*) "Chiptyp";
	r.display_device_dacType = (char*) "DAC-Typ";
	r.display_device_type = (char*) "Gerätetyp";
	r.display_device_mem = (char*) "Gesamtspeicher ca.";
	r.display_device_videoMem = (char*) "Anzeigespeicher (VRAM)";
	r.display_device_sharedMem = (char*) "Gemeinsam genutzter Speicherbereich";
	r.display_device_currDisplayMode = (char*) "Aktueller Anzeigemodus";
	r.display_device_monitor = (char*) "Monitor";
	r.display_driver_label = (char*) "Treiber";
	r.display_driver_mainDriver = (char*) "Haupttreiber";
	r.display_driver_version = (char*) "Version";
	r.display_driver_date = (char*) "Datum";
	r.display_driver_whqlLogo = (char*) "Mit WHQL-Logo";
	r.display_driver_d3dDdi = (char*) "Direct3D-DDI";
	r.display_driver_featureLevels = (char*) "Funktionsebenen";
	r.display_driver_model = (char*) "Treibermodell";
	r.display_features_label = (char*) "DirectX-Features";
	r.display_features_ddAccel = (char*) "DirectDraw-Beschleunigung";
	r.display_features_d3dAccel = (char*) "Direct3D-Beschleunigung";
	r.display_features_agpAccel = (char*) "AGP-Oberflächenbeschleunigung";
	r.display_notes_label = (char*) "Hinweise";

    //Tab Sound
    r.sound_device_label = (char*) "Gerät";
	r.sound_device_name = (char*) "Name";
	r.sound_device_hardwareId = (char*) "Hardware-ID";
	r.sound_device_manufacturerId = (char*) "Herstellerkennung";
	r.sound_device_productId = (char*) "Produktkennung";
	r.sound_device_type = (char*) "Typ";
	r.sound_device_default = (char*) "Standardgerät";
	r.sound_driver_label = (char*) "Treiber";
	r.sound_driver_name = (char*) "Name";
	r.sound_driver_version = (char*) "Version";
	r.sound_driver_date = (char*) "Datum";
	r.sound_driver_whqlLogo = (char*) "Mit WHQL-Logo";
	r.sound_driver_otherFiles = (char*) "Andere Dateien";
	r.sound_driver_provider = (char*) "Anbieter";
	r.sound_notes_label = (char*) "Hinweise";

    return r;
}