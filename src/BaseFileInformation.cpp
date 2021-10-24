#include "FileInformation.hpp"

using namespace Analyzer;

BaseFileInformation::BaseFileInformation() : 
    path("")
{
    lastModificationTime = (time_t)(-1);
}

BaseFileInformation::BaseFileInformation(std::filesystem::path pathToFile) :
    path(pathToFile)
{
    SetInformation();
}

void BaseFileInformation::SetInformation()
{
    SetLastModificationTime();
}

void BaseFileInformation::SetLastModificationTime()
{
    std::filesystem::file_time_type fileLastModificationTime = std::filesystem::last_write_time(path);

    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(fileLastModificationTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

    lastModificationTime = std::chrono::system_clock::to_time_t(sctp);
}

std::string BaseFileInformation::ToString()
{
    std::stringstream buffer;
    buffer << "Name: " << path.filename() << " ";

    if (path.has_parent_path())
        buffer << "Parent name" << path.parent_path().filename() << " ";
    else
        buffer << "Parent name: no parent" <<" ";

    std::tm *gmt = std::gmtime(&lastModificationTime);

    buffer << "Last modification time" << std::put_time(gmt, "%A, %d %B %Y %H:%M") << " ";

    std::string outputString = buffer.str();

    return outputString;
}

std::filesystem::path BaseFileInformation::GetDirectoryPath()
{
    return path;
}
std::time_t BaseFileInformation::GetTime()
{
    return lastModificationTime;
}

bool BaseFileInformation::Equals(BaseFileInformation &object)
{
    return path == object.GetDirectoryPath();
}