#include "RollingHash.hpp"
#include "FileOperations.hpp"

int main(int argc, char** argv)
{
    RollingHash rollingHash;
    FileOperation fileOps;

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

    fileOps.readFile(original_filename, orig_file_content);
    fileOps.readFile(updated_filename, upda_file_content);

    if (argc == 4) 
    {
        std::string chunk = argv[3];
        rollingHash.setChuckSize(std::stoi(chunk));
    }

    rollingHash.compareTwoStrings(orig_file_content, upda_file_content);

    std::string diff_file = (original_filename + "_diff_" + updated_filename);
    fileOps.writeFile(diff_file, rollingHash.getDiff());

    return 0;
}