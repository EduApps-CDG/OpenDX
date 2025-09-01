#pragma once
#include <types/Translation.hpp>
#include "en_US.hpp"

/**
 * TODO Complete with @see project://include/types/Translation.hpp
 */
Translation_t Translation_esES() {
	Translation_t r = Translation_enUS();

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

	//Tab Display
	r.display_device_label = (char*) "Etiqueta del dispositivo de visualización";
	r.display_device_manufacturer = (char*) "Fabricante del dispositivo de visualización";
	r.display_device_chipType = (char*) "Tipo de chip del dispositivo de visualización";
	r.display_device_dacType = (char*) "Tipo de DAC del dispositivo de visualización";
	r.display_device_type = (char*) "Tipo de dispositivo de visualización";
	r.display_device_mem = (char*) "Memoria del dispositivo de visualización";
	r.display_device_videoMem = (char*) "Memoria de vídeo del dispositivo de visualización";
	r.display_device_sharedMem = (char*) "Memoria compartida del dispositivo de visualización";
	r.display_device_currDisplayMode = (char*) "Modo de visualización actual del dispositivo de visualización";
	r.display_device_monitor = (char*) "Monitor del dispositivo de visualización";
	r.display_driver_label = (char*) "Etiqueta del controlador de visualización";
	r.display_driver_mainDriver = (char*) "Controlador principal del controlador de visualización";
	r.display_driver_version = (char*) "Versión del controlador de visualización";
	r.display_driver_date = (char*) "Fecha del controlador de visualización";
	r.display_driver_whqlLogo = (char*) "Logotipo WHQL del controlador de visualización";
	r.display_driver_d3dDdi = (char*) "D3D DDI del controlador de visualización";
	r.display_driver_featureLevels = (char*) "Niveles de características del controlador de visualización";
	r.display_driver_model = (char*) "Modelo del controlador de visualización";
	r.display_features_label = (char*) "Etiqueta de las características de visualización";
	r.display_features_ddAccel = (char*) "Aceleración DD de las características de visualización";
	r.display_features_d3dAccel = (char*) "Aceleración D3D de las características de visualización";
	r.display_features_agpAccel = (char*) "Aceleración AGP de las características de visualización";
	r.display_notes_label = (char*) "Etiqueta de las notas de visualización";

	//Tab Sound
	r.sound_device_label = (char*) "Etiqueta del dispositivo de sonido";
	r.sound_device_name = (char*) "Nombre del dispositivo de sonido";
	r.sound_device_hardwareId = (char*) "ID de hardware del dispositivo de sonido";
	r.sound_device_manufacturerId = (char*) "ID de fabricante del dispositivo de sonido";
	r.sound_device_productId = (char*) "ID de producto del dispositivo de sonido";
	r.sound_device_type = (char*) "Tipo de dispositivo de sonido";
	r.sound_device_default = (char*) "Dispositivo de sonido predeterminado";
	r.sound_driver_label = (char*) "Etiqueta del controlador de sonido";
	r.sound_driver_name = (char*) "Nombre del controlador de sonido";
	r.sound_driver_version = (char*) "Versión del controlador de sonido";
	r.sound_driver_date = (char*) "Fecha del controlador de sonido";
	r.sound_driver_whqlLogo = (char*) "Logotipo WHQL del controlador de sonido";
	r.sound_driver_otherFiles = (char*) "Otros archivos del controlador de sonido";
	r.sound_driver_provider = (char*) "Proveedor del controlador de sonido";
	r.sound_notes_label = (char*) "Etiqueta de las notas de sonido";

	return r;
}
