#include "RollingHash.hpp"
#include "FileOperations.hpp"
#include <fstream>

void testSameFiles()
{
    std::cout << "Testing two same files\n";

    RollingHash rHash;
    FileOperation fOps;

    std::string first = "";
    std::string second = "";
    std::string filename = "demo_files/name.txt";

    fOps.readFile(filename, first);
    fOps.readFile(filename, first);

    //set a smaller chunk size and compare the strings

    rHash.setChuckSize(8);
    rHash.compareTwoStrings(first, second);

    std::string& diff = rHash.getDiff();

    //std::cout << diff << "\n";
    if (diff.find("Mismatch") == std::string::npos)
    {
        std::cout << "Matching two same files is successful. No mismatch is found\n";
    }
    else
    {
        std::cout << "Failed Test:  Matching two same files is unsuccessful. Mismatch is found\n";
    }
}

void testSameLongFiles()
{
    std::cout << "Testing two same long files\n";

    RollingHash rHash;
    FileOperation fOps;

    std::string first = "";
    std::string second = "";
    std::string filename = "demo_files/long_file.txt";

    fOps.readFile(filename, first);
    fOps.readFile(filename, first);

    //set a smaller chunk size and compare the strings

    rHash.setChuckSize(2048);
    rHash.compareTwoStrings(first, second);

    std::string& diff = rHash.getDiff();

    //std::cout << diff << "\n";
    if (diff.find("Mismatch") == std::string::npos)
    {
        std::cout << "Matching two same long files is successful. No mismatch is found\n";
    }
    else
    {
        std::cout << "Failed Test:  Matching two same long files is unsuccessful. Mismatch is found\n";
    }
}

void testDifferentFiles()
{
    std::cout << "Testing two different files\n";

    RollingHash rHash;
    FileOperation fOps;

    std::string first = "";
    std::string second = "";
    std::string filename_first = "demo_files/name.txt";
    std::string filename_second = "demo_files/name_updated.txt";

    fOps.readFile(filename_first, first);
    fOps.readFile(filename_second, second);

    //set a smaller chunk size and compare the strings

    rHash.setChuckSize(8);
    rHash.compareTwoStrings(first, second);

    std::string& diff = rHash.getDiff();

    //std::cout << diff << "\n";
    if (diff.find("Mismatch") != std::string::npos)
    {
        std::cout << "Matching two different files is successful. Mismatch is found\n";
    }
    else
    {
        std::cout << "Failed Test:  Matching two different files is unsuccessful. No mismatch is found\n";
    }
}


int main(int argc, char** argv)
{
    testSameFiles();
    testSameLongFiles();
    testDifferentFiles();

    return 0;
}