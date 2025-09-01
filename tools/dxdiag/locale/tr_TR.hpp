#pragma once
#include <types/Translation.hpp>
#include "en_US.hpp"

/**
 * TODO Completed
 */
Translation_t Translation_trTR() {
	Translation_t r = Translation_enUS();

	//Common texts
	r.yes = (char*)"Evet";
	r.no = (char*)"Hay�r";
	r.not_available = (char*)"Mevcut de�il";
	r.enabled = (char*)"Etkinle�tirilmi�";

	//Tab names
	r.tab_system = (char*)"Sistem";
	r.tab_display = (char*)"Ekran";
	r.tab_sound = (char*)"Ses";
	r.tab_input = (char*)"Girdi";

	//Buttons
	r.btn_help = (char*)"Yard�m";
	r.btn_next = (char*)"�leri";
	r.btn_save = (char*)"Kaydet";
	r.btn_exit = (char*)"��k��";

	//Tab System
	r.system_description = (char*)"Bu ara�, sisteminizde y�kl� olan OpenDX bile�enleri ve s�r�c�leri hakk�nda ayr�nt�l� bilgi rapor eder.\n\nSoruna hangi alan�n neden oldu�unu biliyorsan�z, yukar�daki uygun sekmeye t�klay�n. Aksi takdirde her sayfay� s�rayla ziyaret etmek i�in a�a��daki \"Sonraki Sayfa\" butonunu kullanabilirsiniz.";
	r.system_info_label = (char*)"Sistem bilgisi";
	r.system_info_currentDate = (char*)"Yerel Tarih/Zaman";
	r.system_info_pcName = (char*)"Bilgisayar ad�";
	r.system_info_os = (char*)"Isletim sistemi";
	r.system_info_language = (char*)"Dil";
	r.system_info_manufacturer = (char*)"Sistem �reticisi";
	r.system_info_model = (char*)"Sistem modeli";
	r.system_info_bios = (char*)"BIOS";
	r.system_info_processor = (char*)"��lemci";
	r.system_info_memory = (char*)"Haf�za";
	r.system_info_pageFile = (char*)"Sayfa";
	r.system_info_directxVersion = (char*)"DirectX S�r�m�";
	r.system_info_opendxVersion = (char*)"OpenDX S�r�m�";

	// Tab Display X
	r.display_device_label = (char*)"S�r�c�";
	r.display_device_manufacturer = (char*)"�retici";
	r.display_device_chipType = (char*)"�ip T�r�";
	r.display_device_dacType = (char*)"DAC T�r�";
	r.display_device_type = (char*)"Device T�r�";
	r.display_device_mem = (char*)"Toplam Bellek";
	r.display_device_videoMem = (char*)"Video Belle�i";
	r.display_device_sharedMem = (char*)"Payla��ml� Bellek";
	r.display_device_currDisplayMode = (char*)"Ge�erli G�r�nt� Modu";
	r.display_device_monitor = (char*)"Ekran";
	r.display_driver_label = (char*)"S�r�c�ler";
	r.display_driver_mainDriver = (char*)"Ana S�r�c�";
	r.display_driver_version = (char*)"S�r�m";
	r.display_driver_date = (char*)"Tarih";
	r.display_driver_whqlLogo = (char*)"WHQL Logosu";
	r.display_driver_d3dDdi = (char*)"Direct3D DDI";
	r.display_driver_featureLevels = (char*)"�zellik";
	r.display_driver_model = (char*)"Model";
	r.display_features_ddAccel = (char*)"DD H�zland�rmas�";
	r.display_features_d3dAccel = (char*)"D3D H�zland�rmas�";
	r.display_features_agpAccel = (char*)"AGP H�zland�rmas�";
	r.display_notes_label = (char*)"Notlar";

	// Tab Sound 

	r.sound_device_label = (char*)"Cihaz";
	r.sound_device_name = (char*)"Ad";
	r.sound_device_hardwareId = (char*)"Donan�m Kimli�i";
	r.sound_device_manufacturerId = (char*)"�retici Kimli�i";
	r.sound_device_productId = (char*)"�r�n Kimli�i";
	r.sound_device_type = (char*)"T�r";
	r.sound_device_default = (char*)"Varsay�lan Cihaz";
	r.sound_driver_label = (char*)"S�r�c�ler";
	r.sound_driver_name = (char*)"Ad";
	r.sound_driver_version = (char*)"S�r�m";
	r.sound_driver_date = (char*)"Tarih";
	r.sound_driver_whqlLogo = (char*)"WHQL Logosu";
	r.sound_driver_otherFiles = (char*)"Di�er Dosyalar";
	r.sound_driver_provider = (char*)"Sa�lay�c�";
	r.sound_notes_label = (char*)"Notlar";



	return r;
}
