#pragma once
#include <types/Translation.hpp>

/**
 * TODO Complete with project://include/types/Translation.hpp
 */
Translation_t Translation_itIT() {
	Translation_t r;

	//Common texts
	r.yes = (char*) "Si";
	r.no = (char*) "No";
	r.not_available = (char*) "Non Disponibile";
	r.enabled = (char*) "Abilitato";

	//Tab names
	r.tab_system = (char*) "Sistema";
	r.tab_display = (char*) "Schermo";
	r.tab_sound = (char*) "Audio";
	r.tab_input = (char*) "Input";

	//Buttons
	r.btn_help = (char*) "Aiuto";
	r.btn_next = (char*) "Sucessiva";
	r.btn_save = (char*) "Salva";
	r.btn_exit = (char*) "Esci";

	//Tab System
	r.system_description = (char*) "Questo strumento riporta informazioni dettagliate sui componenti e sui driver OpenDX installati sul tuo sistema.\n\nSe sai quale area causa il problema, fai clic sulla scheda appropriata sopra. Altrimenti puoi usare il pulsante \"Pagina successiva\" qui sotto per visitare ogni pagina in sequenza.";
	r.system_info_label = (char*) "Informazioni di sistema";
	r.system_info_currentDate = (char*) "Data/ora corrente";
	r.system_info_pcName = (char*) "Nome del computer";
	r.system_info_os = (char*) "Systema Operativo";
	r.system_info_language = (char*) "Lingua";
	r.system_info_manufacturer = (char*) "Produttore del sistema";
	r.system_info_model = (char*) "Modello del sistema";
	r.system_info_bios = (char*) "BIOS";
	r.system_info_processor = (char*) "Processore";
	r.system_info_memory = (char*) "Memoria";
	r.system_info_pageFile = (char*) "Page file";
	r.system_info_directxVersion = (char*) "Versione DirectX";
	r.system_info_opendxVersion = (char*) "Versione OpenDX";

//Tab Display
	r.display_device_label = (char*) "Visualizza l'etichetta del dispositivo";
	r.display_device_manufacturer = (char*) "Produttore del dispositivo";
	r.display_device_chipType = (char*) "Visualizza il tipo di chip del dispositivo";
	r.display_device_dacType = (char*) "Tipo di DAC del dispositivo";
	r.display_device_type = (char*) "Tipo di dispositivo";
	r.display_device_mem = (char*) "Memoria del dispositivo";
	r.display_device_videoMem = (char*) "Memoria vídeo del dispositivo";
	r.display_device_sharedMem = (char*) "Memoria del dispositivo condivisa";
	r.display_device_currDisplayMode = (char*) "Modalità di visualizzazione corrente del dispositivo";
	r.display_device_monitor = (char*) "Visualizza il monitor del dispositivo";
	r.display_driver_label = (char*) "Visualizza l'etichetta del controller";
	r.display_driver_mainDriver = (char*) "Controller principale del controller video";
	r.display_driver_version = (char*) "Visualizza la versione del driver";
	r.display_driver_date = (char*) "Visualizza la data del controller";
	r.display_driver_whqlLogo = (char*) "Visualizza il logo WHQL del controller";
	r.display_driver_d3dDdi = (char*) "Driver video D3D DDI";
	r.display_driver_featureLevels = (char*) "Livelli di funzionalità del controller video";
	r.display_driver_model = (char*) "Modello del controller video";
	r.display_features_label = (char*) "Etichetta delle funzioni di visualizzazione";
	r.display_features_ddAccel = (char*) "Accelerazione DD delle funzionalità di visualizzazione";
	r.display_features_d3dAccel = (char*) "Accelerazione D3D delle funzionalità di visualizzazione";
	r.display_features_agpAccel = (char*) "Accelerazione AGP delle funzionalità di visualizzazione";
	r.display_notes_label = (char*) "Visualizza etichetta note";

	//Tab Sound
	r.sound_device_label = (char*) "Etichetta del dispositivo audio";
	r.sound_device_name = (char*) "Nome del dispositivo audio";
	r.sound_device_hardwareId = (char*) "ID hardware del dispositivo audio";
	r.sound_device_manufacturerId = (char*) "ID del produttore del dispositivo audio";
	r.sound_device_productId = (char*) "ID prodotto del dispositivo audio";
	r.sound_device_type = (char*) "Tipo di dispositivo audio";
	r.sound_device_default = (char*) "Dispositivo audio predefinito";
	r.sound_driver_label = (char*) "Etichetta del driver audio";
	r.sound_driver_name = (char*) "Nome del driver audio";
	r.sound_driver_version = (char*) "Versione del driver audio";
	r.sound_driver_date = (char*) "Data del driver audio";
	r.sound_driver_whqlLogo = (char*) "Logo WHQL del controller audio";
	r.sound_driver_otherFiles = (char*) "Altri file dei driver audio";
	r.sound_driver_provider = (char*) "Fornitore di driver audio";
	r.sound_notes_label = (char*) "Etichetta della nota sonora";

	return r;
}
