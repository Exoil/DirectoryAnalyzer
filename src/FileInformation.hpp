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
            std::string content;
    };

    class DirectoryInformation :
        public BaseFileInformation
    {
    public:        
        DirectoryInformation(std::filesystem::path pathToDirectory);
        void SetInformation() override;
        std::string ToString() override;
    protected:
        unsigned int countElementContent = 0;
    };

    class FileInformation :
        public BaseFileInformation
    {
        public:
            FileInformation(std::filesystem::path pathToDirectory);          
            void SetInformation() override;
            std::string ToString() override;
            void SetContent();
            void SetContent(std::string content);
            std::string GetContent();
            unsigned int GetCountWords();
            unsigned int GetCountCharacters();
        protected:
            size_t _size;
            std::string _content;
            std::string _extension = "";
    };
}