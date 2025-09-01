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
#define GetFileContent(file_path) #file_path
