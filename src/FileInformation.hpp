#pragma once
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <chrono>

namespace Analyzer
{
    class BaseFileInformation
    {
    public:
        BaseFileInformation();
        BaseFileInformation(std::filesystem::path pathToFile);
        std::filesystem::path GetDirectoryPath();
        std::time_t GetTime();
        bool Equals(BaseFileInformation &object);
        void SetLastModificationTime();
        virtual void SetInformation();
        virtual std::string ToString();

    protected:
        std::filesystem::path path;
        std::time_t lastModificationTime;
    };

    class DirectoryInformation : public BaseFileInformation
    {
    public:
        DirectoryInformation(std::filesystem::path pathToDirectory);
        void SetInformation() override;
        std::string ToString() override;

    protected:
        unsigned int countElementContent = 0;
    };

    class FileInformation : public BaseFileInformation
    {
    public:
        FileInformation(std::filesystem::path pathToDirectory);
        void SetInformation() override;
        std::string ToString() override;

    protected:
        size_t size;
        std::string extension = "";
        unsigned int countWords = 0;
        unsigned int countCharacters = 0;

    private:
        std::string ReadFile();
        void SetCountWords(std::string fileContent);
        void SetCountCharacters(std::string fileContent);
    };
}
