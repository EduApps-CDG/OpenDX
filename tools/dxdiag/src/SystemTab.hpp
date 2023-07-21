#pragma once
#include <gtk/gtk.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sys/sysinfo.h>

namespace SystemTab {
	/**
	 * Set the text from "date_val"to the actual date/time.
	 */
	gboolean updateTime(GtkLabel* label) {
		time_t t = time(NULL);
		struct tm *time = localtime(&t);
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
	gboolean onRealizeTime(GtkLabel* label) {
		std::cout << "SystemTab::onRealizeTime()\n";

		g_timeout_add (500, (GSourceFunc) SystemTab::updateTime, label);
		return FALSE;
	}

	/**
	 * Set the text from "pc_val" to the unix hostname.
	 */
	gboolean setHostname(GtkLabel* label) {
		char hostname[1024];
		gethostname(hostname, sizeof hostname);


		gtk_label_set_text(label, hostname);

		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	std::string exec(const char* cmd) {
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

	gboolean setOperatingSystem(GtkLabel* label) {
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

		// Convert the string to const gchar*
		const gchar* text = os_info.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	gboolean setLanguage(GtkLabel* label) {
		char buffer[128];
		std::string lang, region;

		// Get the LC_MESSAGES locale
		std::FILE* fp = popen("locale | grep LC_MESSAGES | cut -d= -f2 | cut -d_ -f1", "r");
		std::fgets(buffer, 128, fp);
		lang = buffer;
		pclose(fp);

		// Get the LC_CTYPE locale
		fp = popen("locale | grep LC_CTYPE | cut -d= -f2 | cut -d_ -f2", "r");
		std::fgets(buffer, 128, fp);
		region = buffer;
		pclose(fp);

		// Remove newline characters
		lang.erase(lang.size() - 1, 1);
		region.erase(region.size() - 1, 1);

		// Return the formatted string
		std::string str = lang + " (Regional Setting: " + region + ")";
		const gchar* text = str.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	gboolean setManufacturer(GtkLabel* label) {
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

	gboolean setModel(GtkLabel* label) {
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

	gboolean setBIOS(GtkLabel* label) {
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

	std::string getCpuModelName() {
		std::ifstream file("/proc/cpuinfo");
		std::string line;

		while (std::getline(file, line)) {
			if (line.find("model name") != std::string::npos) {
				return line.substr(line.find(":") + 2);
			}
		}

		return "Unknown";
	}

	int getCpuCoreCount() {
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

	double getCpuFrequency() {
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

	std::string getCpuInfo() {
		int core_count = getCpuCoreCount();
		double frequency = getCpuFrequency() / 1000;
		std::string model_name = getCpuModelName();

		std::ostringstream frequency_stream;
		frequency_stream << std::fixed << std::setprecision(2) << frequency / core_count;
		std::string formatted_frequency = frequency_stream.str();

		return model_name + " (" + std::to_string(core_count) + " CPUs), ~" + formatted_frequency + "GHz";
	}

	gboolean setCPU(GtkLabel* label) {
		std::string cpu = SystemTab::getCpuInfo();
		const gchar* text = cpu.c_str();

		gtk_label_set_text(label, text);
		gtk_widget_queue_draw(GTK_WIDGET(label));
		gtk_widget_queue_draw(gtk_widget_get_parent(GTK_WIDGET(label)));
		gtk_widget_show(GTK_WIDGET(label));

		return FALSE;
	}

	gboolean setRAM(GtkLabel* label) {
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

	gboolean updateSwap(GtkLabel* label) {

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
	}

	gboolean setSwap(GtkLabel* label) {
		g_timeout_add (500, (GSourceFunc) SystemTab::updateSwap, label);
		return FALSE;
	}

	/**
	 * setup IDs and it's events
	 */
	void setup(GtkBuilder* builder) {
		std::cout << "SystemTab::setup()\n";

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
}
