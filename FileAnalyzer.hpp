#pragma once
#include "FileInfo.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace Analyzer
{
    class FileAnalyzer
    {
    public:
        void AnaylzeDirectorySingleThread(FileInfo file);
        // void AnaylzeDirectoryMultiThread(FileInfo file);
        int CountWordsInFile(FileInfo *file);
        int CountCharactersInFile(FileInfo *file);
    private:
        std::string ReadFileIntoString(const std::string &path);
    };
}