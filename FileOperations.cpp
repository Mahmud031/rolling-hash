#include "FileOperations.hpp"

FileOperation::FileOperation()
{
    //std::cout << "Creating File Operation Object\n";
}

FileOperation::~FileOperation()
{
    //std::cout << "Destructing File Operation Object\n";
}

void FileOperation::readFile(std::string& filename, std::string& file_content)
{
    std::fstream new_file;

    new_file.open(filename, std::ios::in);

    if (!new_file.is_open())
    {
        std::cout << "Error while opening the file  " << filename << "\n";
        return;
    }

    std::string line;

    while(getline(new_file, line))
    {
        file_content += line;
    }

    new_file.close();
}

void FileOperation::writeFile(std::string& filename, std::string& file_content)
{
    std::fstream new_file;

    new_file.open(filename, std::ios::out);

    if (!new_file.is_open())
    {
        std::cout << "Error while opening the file  " << filename << "\n";
        return;
    }

    new_file << file_content;

    new_file.close();
}
