#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include <fstream>
#include <iostream>

/**
 * @class FileOperation
 * @brief Defines the FileOperation class.
 */
class FileOperation
{
public:
    /**
     * @brief Constructor of a RollingHash class
     */
    explicit FileOperation();

    /**
     * @brief Destructor of a RollingHash class
     */
    ~FileOperation();

    /**
     * @brief Reads the given file
     * @param filename File to be read
     * @param file_content File content is stored here
     */

    void readFile(std::string& filename, std::string& file_content);

    /**
     * @brief Writes the given file
     * @param filename File to be written
     * @param file_content contents to be written
     */

    void writeFile(std::string& filename, std::string& file_content);
};

#endif