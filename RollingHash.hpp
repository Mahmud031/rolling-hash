#ifndef ROLLING_HASH
#define ROLLING_HASH

#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>

/**
 * @class RollingHash
 * @brief Defines the RollingHash class.
 */
class RollingHash 
{

public:
    /**
     * @brief Constructor of a RollingHash class
     */
    explicit RollingHash();

    /**
     * @brief Destructor of a RollingHash class
     */
    ~RollingHash();

    /**
     * @brief Updates the Chunk Size
     * @param chunk_size chunk size
     */

    void setChuckSize(int size);    

    /**
     * @brief Comapres the updated strings against the original string
     * @param original original string
     * @param updated updated string
     */

    void compareTwoStrings(std::string& original, std::string& updated);

    /**
     * @brief Returns the diff string
     * @return reference to the diff string
     */

    std::string& getDiff();

    /**
     * @brief Store the diff information of the compared files
     */

    std::string diff = "";

private:
    /**
     * @brief Calculates the hash value of the input string from 
     *        start to end index.
     * @param hash_string input string
     * @param start start index for hash calculation
     * @param end end index for hash calculation
     * @return long long, calculated hash value
     */

    long long calculateHash(std::string& hash_string, int start, int end);

    /**
     * @brief Calculates the rolling hash value of the input string from 
     *        start to end index.
     * @param hash_string input string
     * @param previous_hash previous Hash value
     * @param start start index for hash calculation
     * @param end end index for hash calculation
     * @return updates the previous_hash
     */

    void calculateRollingHash(std::string& hash_string, long long& previous_hash, int start, int end);

    /**
     * @brief Calculates the rolling hash value of the input string from 
     *        first to last index and store them in a map.
     * @param hash_string input string
     * @param hash_map a map to store the hash values
     * @return updates the hash_map with the hash values
     */

    void storeRollingHash(std::string& hash_string, std::unordered_map<long long, int>& hash_map);

    /**
     * @brief Calculates the power of the base value
     * @param power value of power
     * @return long long, calculated power of base
     */

    long long powerOfBase(int power);

    /**
     * @brief Define the base number for hash calculation
     */

    const long long BASE_NUM = 29791;

    /**
     * @brief Define the mod number for hash calculation
     */

    const long long MOD_NUM = 100000007;

    /**
     * @brief Define the chunk size for splitting the data
     */

    int CHUNK_SIZE = 64;

    /**
     * @brief Define the power of base for rolling hash calculation
     */

    long long BASE_POWER_ROLLING_HASH = -1;

};

#endif