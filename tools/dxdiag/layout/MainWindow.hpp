#pragma once
#include <preprocessor/GetFileContent.hpp>
#include <string>

namespace MainWindow {
	const std::string ui = GetFileContent(PROJECT_SOURCE_DIR "/tools/dxdiag/layout/MainWindow.ui");
}
