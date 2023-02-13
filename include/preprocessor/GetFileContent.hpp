#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/**
 * Caution: by using that function,
 * it means that every time it's called
 * the file content will be included in the code
 */
#define GetFileContent(file_path) []() -> std::string { \
    std::ifstream file(file_path); \
    std::stringstream buffer; \
    buffer << file.rdbuf(); \
    return buffer.str(); \
}()
