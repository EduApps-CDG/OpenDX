#pragma once
#include <unistd.h>
#include <iostream>
#include <locale>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <regex>
#include <cstring>
#include <iomanip>
#include <sys/sysinfo.h>

#include <gtk/gtk.h>

#include <types/Translation.hpp>
#include "../locale/en_US.hpp"
#include "../locale/pt_BR.hpp"
#include "../locale/es_ES.hpp"

class SystemTab {
	/**
	 * Set the text from "date_val"to the actual date/time.
	 */
	public:static gboolean updateTime(GtkLabel* label) {
		time_t t = time(NULL);
		struct tm* time = localtime(&t);
		gchar str_time[40];

		strftime(str_time, sizeof(str_time), "%A, %b %d, %Y, %I:%M:%S %p", time);
		gtk_label_set_text(label, str_time);

		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return G_SOURCE_CONTINUE;
	}

	/**
	 * set a timeout event every 500ms to set the actual date/time
	 */
	public:static gboolean onRealizeTime(GtkLabel* label) {
		std::cout << "SystemTab::onRealizeTime()\n";

		g_timeout_add (500, (GSourceFunc) SystemTab::updateTime, label);
		return FALSE;
	}

	/**
	 * Set the text from "pc_val" to the unix hostname.
	 */
	public:static gboolean setHostname(GtkLabel* label) {
		char hostname[1024];
		gethostname(hostname, sizeof hostname);


		gtk_label_set_text(label, hostname);

		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static std::string exec(const char* cmd) {
		std::vector<char> buffer(1024);
		std::string result;
		FILE* pipe = popen(cmd, "r");

		if (!pipe) throw std::runtime_error("popen() failed!");

		while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}

		pclose(pipe);
		return result;
	}

	public:static gboolean setOperatingSystem(GtkLabel* label) {
		std::string distro = exec("lsb_release -i | awk '{print $3}'");
		std::string distro_version = exec("lsb_release -r | awk '{print $2}'");
		std::string kernel_version = exec("uname -r");
		std::string arch = exec("uname -m | grep -q 64 && echo 64-bit || echo 32-bit");

		// Trim the string values
		//distro.erase(std::remove(distro.begin(), distro.c_str() '\n'), distro.end());
		//distro_version.erase(std::remove(distro_version.begin(), distro_version.end(), '\n'), distro_version.end());
		//kernel_version.erase(std::remove(kernel_version.begin(), kernel_version.end(), '\n'), kernel_version.end());
		//arch.erase(std::remove(arch.begin(), arch.end(), '\n'), arch.end());

		std::string os_info = distro + " " + arch + " (" + distro_version + ", kernel " + kernel_version + ")";
		os_info = std::regex_replace(os_info, std::regex("\n"), "");
		
		// Convert the string to const gchar*
		const gchar* text = os_info.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean setLanguage(GtkLabel* label) {
		char buffer[128];
		std::string locale = setlocale(LC_CTYPE, NULL);
		std::string lang, region;

		// get the language and region from the locale
		lang = locale.substr(0, locale.find("_"));
		region = locale.substr(locale.find("_") + 1);
		region.erase(region.size() - 1, 1);
		region = region.substr(0, region.find("."));

		// Return the formatted string
		std::string str = lang + " (Regional Setting: " + region + ")";
		const gchar* text = str.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean setManufacturer(GtkLabel* label) {
		std::ifstream file("/sys/class/dmi/id/sys_vendor");
		std::string manufacturer;

		if (file.is_open()) {
			std::getline(file, manufacturer);
		}

		const gchar* text = manufacturer.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean setModel(GtkLabel* label) {
		std::ifstream file("/sys/class/dmi/id/product_name");
		std::string model;

		if (file.is_open()) {
			std::getline(file, model);
		}

		const gchar* text = model.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean setBIOS(GtkLabel* label) {
		std::ifstream file("/sys/class/dmi/id/bios_version");
		std::string bios;

		if (file.is_open()) {
			std::getline(file, bios);
		}

		const gchar* text = bios.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static std::string getCpuModelName() {
		std::ifstream file("/proc/cpuinfo");
		std::string line;

		while (std::getline(file, line)) {
			if (line.find("model name") != std::string::npos) {
				return line.substr(line.find(":") + 2);
			}
		}

		return "Unknown";
	}

	public:static int getCpuCoreCount() {
		std::ifstream file("/proc/cpuinfo");
		std::string line;
		int core_count = 0;

		while (std::getline(file, line)) {
			if (line.find("processor") != std::string::npos) {
				++core_count;
			}
		}

		return core_count;
	}

	public:static double getCpuFrequency() {
		std::ifstream file("/proc/cpuinfo");
		std::string line;
		double frequency = 0.0;

		while (std::getline(file, line)) {
			if (line.find("cpu MHz") != std::string::npos) {
				frequency += std::stod(line.substr(line.find(":") + 1));
			}
		}

		return frequency;
	}

	public:static std::string getCpuInfo() {
		int core_count = SystemTab::getCpuCoreCount();
		double frequency = SystemTab::getCpuFrequency() / 1000;
		std::string model_name = SystemTab::getCpuModelName();

		std::ostringstream frequency_stream;
		frequency_stream << std::fixed << std::setprecision(2) << frequency / core_count;
		std::string formatted_frequency = frequency_stream.str();

		return model_name + " (" + std::to_string(core_count) + " CPUs), ~" + formatted_frequency + "GHz";
	}

	public:static gboolean setCPU(GtkLabel* label) {
		std::string cpu = SystemTab::getCpuInfo();
		const gchar* text = cpu.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		// gtk_widget_show(GTK_WIDGET(label));
		return FALSE;
	}

	public:static gboolean setRAM(GtkLabel* label) {
		std::ifstream file("/proc/meminfo");
		std::string line;
		std::string ram = "0MB RAM";

		while (std::getline(file, line)) {
			if (line.find("MemTotal") != std::string::npos) {
				int mb = std::stoi(line.substr(line.find(":") + 1)) / 1024;
				ram = std::to_string(mb) + "MB RAM";
			}
		}

		const gchar* text = ram.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean updateSwap(GtkLabel* label) {
		struct sysinfo info;
		sysinfo(&info);

		const int used = (info.totalswap - info.freeswap) / (1024 * 1024);
		const int available = info.freeswap / (1024 * 1024);
		std::string swap =  std::to_string(used) + "MB used, " + std::to_string(available) + "MB available";

		const gchar* text = swap.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	public:static gboolean setSwap(GtkLabel* label) {
		g_timeout_add(500, (GSourceFunc) SystemTab::updateSwap, label);
		return FALSE;
	}

	/**
	 * setup IDs and it's events
	 */
	public:SystemTab(GtkBuilder* builder) {
		std::cout << "SystemTab::setup()\n";

		this->setupLang(builder);
		this->setupSignals(builder);
	}

	private:void setupLang(GtkBuilder* builder) {
		//get system locale
		const char* locale = setlocale(LC_CTYPE, NULL);
		Translation_t lang;

		//instantiate Translation_{locale}() from tools/dxdiag/locale/{locale}.hpp
		if (
			strcmp(locale, "pt_BR.UTF-8") == 0 ||
			strcmp(locale, "pt_PT.UTF-8") == 0
		) {
			lang = Translation_ptBR(); // >:)
		} else if (strcmp(locale, "es_ES.UTF-8")) {
			lang = Translation_esES();
		} else {
			lang = Translation_enUS();
		}

		//set texts
		GtkLabel* tab_system = GTK_LABEL(gtk_builder_get_object(builder, "tab_system_txt"));
		gtk_label_set_text(tab_system, lang.tab_system);
		GtkLabel* system_description = GTK_LABEL(gtk_builder_get_object(builder, "system_description"));
		gtk_label_set_text(system_description, lang.system_description);
		GtkLabel* system_info_label = GTK_LABEL(gtk_builder_get_object(builder, "system_info_label"));
		gtk_label_set_text(system_info_label, lang.system_info_label);
		GtkLabel* system_info_currentDate = GTK_LABEL(gtk_builder_get_object(builder, "system_info_currentDate"));
		gtk_label_set_text(system_info_currentDate, lang.system_info_currentDate);
		GtkLabel* system_info_pcName = GTK_LABEL(gtk_builder_get_object(builder, "system_info_pcName"));
		gtk_label_set_text(system_info_pcName, lang.system_info_pcName);
		GtkLabel* system_info_os = GTK_LABEL(gtk_builder_get_object(builder, "system_info_os"));
		gtk_label_set_text(system_info_os, lang.system_info_os);
		GtkLabel* system_info_language = GTK_LABEL(gtk_builder_get_object(builder, "system_info_language"));
		gtk_label_set_text(system_info_language, lang.system_info_language);
		GtkLabel* system_info_manufacturer = GTK_LABEL(gtk_builder_get_object(builder, "system_info_manufacturer"));
		gtk_label_set_text(system_info_manufacturer, lang.system_info_manufacturer);
		GtkLabel* system_info_model = GTK_LABEL(gtk_builder_get_object(builder, "system_info_model"));
		gtk_label_set_text(system_info_model, lang.system_info_model);
		GtkLabel* system_info_bios = GTK_LABEL(gtk_builder_get_object(builder, "system_info_bios"));
		gtk_label_set_text(system_info_bios, lang.system_info_bios);
		GtkLabel* system_info_processor = GTK_LABEL(gtk_builder_get_object(builder, "system_info_processor"));
		gtk_label_set_text(system_info_processor, lang.system_info_processor);
		GtkLabel* system_info_memory = GTK_LABEL(gtk_builder_get_object(builder, "system_info_memory"));
		gtk_label_set_text(system_info_memory, lang.system_info_memory);
		GtkLabel* system_info_pageFile = GTK_LABEL(gtk_builder_get_object(builder, "system_info_pageFile"));
		gtk_label_set_text(system_info_pageFile, lang.system_info_pageFile);
		GtkLabel* system_info_directxVersion = GTK_LABEL(gtk_builder_get_object(builder, "system_info_directxVersion"));
		gtk_label_set_text(system_info_directxVersion, lang.system_info_directxVersion);
		GtkLabel* system_info_opendxVersion = GTK_LABEL(gtk_builder_get_object(builder, "system_info_opendxVersion"));
		gtk_label_set_text(system_info_opendxVersion, lang.system_info_opendxVersion);
	}

	private:void setupSignals(GtkBuilder* builder) {
		GtkLabel* date_val = GTK_LABEL(gtk_builder_get_object(builder, "date_val"));
		g_signal_connect (date_val, "realize", G_CALLBACK (SystemTab::onRealizeTime), NULL);
		GtkLabel* pc_val = GTK_LABEL(gtk_builder_get_object(builder, "pc_val"));
		g_signal_connect (pc_val, "realize", G_CALLBACK (SystemTab::setHostname), NULL);
		GtkLabel* os_val = GTK_LABEL(gtk_builder_get_object(builder, "os_val"));
		g_signal_connect (os_val, "realize", G_CALLBACK (SystemTab::setOperatingSystem), NULL);
		GtkLabel* lang_val = GTK_LABEL(gtk_builder_get_object(builder, "lang_val"));
		g_signal_connect (lang_val, "realize", G_CALLBACK (SystemTab::setLanguage), NULL);
		GtkLabel* pcman_val = GTK_LABEL(gtk_builder_get_object(builder, "pcman_val"));
		g_signal_connect (pcman_val, "realize", G_CALLBACK (SystemTab::setManufacturer), NULL);
		GtkLabel* pcmod_val = GTK_LABEL(gtk_builder_get_object(builder, "pcmod_val"));
		g_signal_connect (pcmod_val, "realize", G_CALLBACK (SystemTab::setModel), NULL);
		GtkLabel* bios_val = GTK_LABEL(gtk_builder_get_object(builder, "bios_val"));
		g_signal_connect (bios_val, "realize", G_CALLBACK (SystemTab::setBIOS), NULL);
		GtkLabel* cpu_val = GTK_LABEL(gtk_builder_get_object(builder, "cpu_val"));
		g_signal_connect (cpu_val, "realize", G_CALLBACK (SystemTab::setCPU), NULL);
		GtkLabel* ram_val = GTK_LABEL(gtk_builder_get_object(builder, "ram_val"));
		g_signal_connect (ram_val, "realize", G_CALLBACK (SystemTab::setRAM), NULL);
		GtkLabel* swap_val = GTK_LABEL(gtk_builder_get_object(builder, "swap_val"));
		g_signal_connect (swap_val, "realize", G_CALLBACK (SystemTab::setSwap), NULL);
	}
};
