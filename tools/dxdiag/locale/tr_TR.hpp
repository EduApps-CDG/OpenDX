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
	r.no = (char*)"Hayýr";
	r.not_available = (char*)"Mevcut deðil";
	r.enabled = (char*)"Etkinleþtirilmiþ";

	//Tab names
	r.tab_system = (char*)"Sistem";
	r.tab_display = (char*)"Ekran";
	r.tab_sound = (char*)"Ses";
	r.tab_input = (char*)"Girdi";

	//Buttons
	r.btn_help = (char*)"Yardým";
	r.btn_next = (char*)"Ýleri";
	r.btn_save = (char*)"Kaydet";
	r.btn_exit = (char*)"Çýkýþ";

	//Tab System
	r.system_description = (char*)"Bu araç, sisteminizde yüklü olan OpenDX bileþenleri ve sürücüleri hakkýnda ayrýntýlý bilgi rapor eder.\n\nSoruna hangi alanýn neden olduðunu biliyorsanýz, yukarýdaki uygun sekmeye týklayýn. Aksi takdirde her sayfayý sýrayla ziyaret etmek için aþaðýdaki \"Sonraki Sayfa\" butonunu kullanabilirsiniz.";
	r.system_info_label = (char*)"Sistem bilgisi";
	r.system_info_currentDate = (char*)"Yerel Tarih/Zaman";
	r.system_info_pcName = (char*)"Bilgisayar adý";
	r.system_info_os = (char*)"Isletim sistemi";
	r.system_info_language = (char*)"Dil";
	r.system_info_manufacturer = (char*)"Sistem üreticisi";
	r.system_info_model = (char*)"Sistem modeli";
	r.system_info_bios = (char*)"BIOS";
	r.system_info_processor = (char*)"Ýþlemci";
	r.system_info_memory = (char*)"Hafýza";
	r.system_info_pageFile = (char*)"Sayfa";
	r.system_info_directxVersion = (char*)"DirectX Sürümü";
	r.system_info_opendxVersion = (char*)"OpenDX Sürümü";

	// Tab Display X
	r.display_device_label = (char*)"Sürücü";
	r.display_device_manufacturer = (char*)"Üretici";
	r.display_device_chipType = (char*)"Çip Türü";
	r.display_device_dacType = (char*)"DAC Türü";
	r.display_device_type = (char*)"Device Türü";
	r.display_device_mem = (char*)"Toplam Bellek";
	r.display_device_videoMem = (char*)"Video Belleði";
	r.display_device_sharedMem = (char*)"Paylaþýmlý Bellek";
	r.display_device_currDisplayMode = (char*)"Geçerli Görüntü Modu";
	r.display_device_monitor = (char*)"Ekran";
	r.display_driver_label = (char*)"Sürücüler";
	r.display_driver_mainDriver = (char*)"Ana Sürücü";
	r.display_driver_version = (char*)"Sürüm";
	r.display_driver_date = (char*)"Tarih";
	r.display_driver_whqlLogo = (char*)"WHQL Logosu";
	r.display_driver_d3dDdi = (char*)"Direct3D DDI";
	r.display_driver_featureLevels = (char*)"Özellik";
	r.display_driver_model = (char*)"Model";
	r.display_features_ddAccel = (char*)"DD Hýzlandýrmasý";
	r.display_features_d3dAccel = (char*)"D3D Hýzlandýrmasý";
	r.display_features_agpAccel = (char*)"AGP Hýzlandýrmasý";
	r.display_notes_label = (char*)"Notlar";

	// Tab Sound 

	r.sound_device_label = (char*)"Cihaz";
	r.sound_device_name = (char*)"Ad";
	r.sound_device_hardwareId = (char*)"Donaným Kimliði";
	r.sound_device_manufacturerId = (char*)"Üretici Kimliði";
	r.sound_device_productID = (char*)"Ürün Kimliði;
	r.sound_device_type = (char*)"Tür";
	r.sound_device_default = (char*)"Varsayýlan Cihaz";
	r.sound_driver_label = (char*)"Sürücüler";
	r.sound_driver_name = (char*)"Ad";
	r.sound_driver_version = (char*)"Sürüm";
	r.sound_driver_date = (char*)"Tarih";
	r.sound_driver_whqlLogo = (char*)"WHQL Logosu";
	r.sound_driver_otherFiles = (char*)"Diðer Dosyalar";
	r.sound_driver_provider = (char*)"Saðlayýcý";
	r.sound_notes_label = (char*)"Notlar";



	return r;
}
