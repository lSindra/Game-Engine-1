#pragma once

#include <stdio.h>
#include <vector>

class FileReader
{
    public: static std::vector<char> readFile(const std::string& filename);
};

