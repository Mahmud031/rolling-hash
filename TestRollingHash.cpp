#include "RollingHash.hpp"
#include <fstream>

void readFile(std::string& filename, std::string& file_content)
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

void writeFile (std::string& filename, std::string& file_content)
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

int main(int argc, char** argv)
{
    RollingHash rollingHash;

    // take the file names

    if (argc < 3)
    {
        std::cout << "Please insert the original and updated file.";
        return 0;
    }

    std::string original_filename = argv[1];
    std::string updated_filename = argv[2];

    std::string orig_file_content = "";
    std::string upda_file_content = "";

    readFile(original_filename, orig_file_content);
    readFile(updated_filename, upda_file_content);

    if (argc == 4) 
    {
        std::string chunk = argv[3];
        rollingHash.setChuckSize(std::stoi(chunk));
    }

    rollingHash.compareTwoStrings(orig_file_content, upda_file_content);

    std::string diff_file = (original_filename + "_diff_" + updated_filename);
    writeFile(diff_file, rollingHash.getDiff());

    return 0;
}