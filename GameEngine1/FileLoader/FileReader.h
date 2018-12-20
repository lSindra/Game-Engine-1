#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

class FileReader
{
public:
    static vector<char> readFile(const string& filename);
};

