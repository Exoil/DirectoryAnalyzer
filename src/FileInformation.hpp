#pragma once
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

namespace Analyzer
{
    class BaseFileInformation
    {
        public:
            BaseFileInformation(std::filesystem::path pathToFile);
            virtual void SetInformation();
            virtual std::string ToString();
        protected:
            std::filesystem::path path;
            time_t lastModificationTime;
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
        protected:
            size_t size;
            std::string extension = "";
            unsigned int countWords = 0;
            unsigned int countCharacters = 0;
        private:
            std::string ReadFile();
            void SetCountWords();
            void SetCountCharacters();
    };
}