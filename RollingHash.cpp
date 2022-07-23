#include "RollingHash.hpp"

RollingHash::RollingHash()
{
    std::cout << "Creating Rolling Hash Object\n";
}

RollingHash::~RollingHash()
{
    std::cout << "Destructing Rolling Hash Object\n";
}

void RollingHash::setChuckSize(int size)
{
    CHUNK_SIZE = size;
    std::cout << "Using custom chunk size:  " << CHUNK_SIZE << "\n";

}

void RollingHash::compareTwoStrings(std::string& original, std::string& updated)
{
    // check the chunk size and modify it if the data is smaller than the chunk

    int original_size = original.size();
    int updated_size = updated.size();

    CHUNK_SIZE = std::min(CHUNK_SIZE, std::min(original_size, updated_size));
    BASE_POWER_ROLLING_HASH = powerOfBase(CHUNK_SIZE-1);

    //std::cout << "Chunk size & Power of Base    " << CHUNK_SIZE << "    " << BASE_POWER_ROLLING_HASH << "\n";

    if (updated_size == 0)
    {
        diff += "Everything is removed in the updated file\n";
        return;
    }

    if (original_size == 0)
    {
        diff += "Everything is added in the updated file\n";
        return;
    }

    // store the hash values of the each offset of the original file.
    // later this will help to check whether the chunk of the updated 
    // file located in the original file or not

    std::unordered_map<long long, int> map_rolling_hash_orig;
    storeRollingHash(original, map_rolling_hash_orig);

    // now run rolling hash in the updated file, if the chunk hash
    // matches with the hash of a chunk of the original file, update
    // diff. If there's a mismatch at any offset of the updated file
    // store that mismatch in the diff

    int i = 0;
    long long hash_updated = 0;
    while (i <= updated_size - CHUNK_SIZE)
    {
        // calculate the hash value of the chunk
        calculateRollingHash(updated, hash_updated, i + CHUNK_SIZE - 1, i+CHUNK_SIZE-1);

        //std::cout << "Hash value for updated    " << hash_updated << "\n";

        if (map_rolling_hash_orig.find(hash_updated) != map_rolling_hash_orig.end()) {
            // this chunk is present in the original string
            // adding the information in the diff

            if (i % CHUNK_SIZE == 0)
            {
                // it's a new chunk and a match, update the info
                diff += ("Chunk:  " + std::to_string(i/CHUNK_SIZE) + "    match with, Chunk:  "
                        + std::to_string(map_rolling_hash_orig[hash_updated]/CHUNK_SIZE) + ",   Position:    " 
                         + std::to_string(map_rolling_hash_orig[hash_updated] % CHUNK_SIZE) + "\n");
            }

            //std::cout << "Match found at    " << map_rolling_hash_orig[hash_updated] << "\n";
        }
        else
        {
            // No match found
            diff += ("       Mismatch at Chunk:    " + std::to_string(i/CHUNK_SIZE) + ",   position    " +
                        std::to_string(i%CHUNK_SIZE) + "\n");

            /*std::cout << "Checking the rolling hash of the updated file\n";*/
        }
        
        i++;
    }
    //std::cout << diff << "\n";

}

std::string& RollingHash::getDiff()
{
    return diff;
}

/** 
 * The hash value is calculated from the following formula,
 * for a string s of size n,
 * h(s) = (s[0]*base^n-1 + s[1]*base^n-2 + s[2]*base^n-3 + . . . + s[n-1]) mod M
 * where base is the BASE_NUM and M is MOD_NUM
 * 
 * From this we can calculate the rolling hash,
 * new_hash = (old_hash - (s[i]*base^CHUNK_SIZE-1) * base + s[j]) mod M
 * where, s[i] is the first character of the chunk which is removed and s[j]
 * is the newly added chracter in the calculation
 */

long long RollingHash::calculateHash(std::string& hash_string, int start, int end)
{
    long long hash = 0;

    for (int i = start; i <= end; ++i)
    {
        hash *= BASE_NUM;
        hash += hash_string[i];
        hash %= MOD_NUM;

        //std::cout << "Calculating hash   " << hash_string[i] << "\n";
    }

    return hash;
}

void RollingHash::calculateRollingHash(std::string& hash_string, long long& previous_hash, int start, int end)
{
    if (previous_hash == 0 || start - CHUNK_SIZE < 0)
    {
        //it's a new hash value
        previous_hash = calculateHash(hash_string, end - CHUNK_SIZE, end);
        return;
    }

    long long new_hash;
    while (start <= end)
    {
        new_hash = ((previous_hash - (hash_string[start - CHUNK_SIZE] * BASE_POWER_ROLLING_HASH)) 
                    * BASE_NUM + hash_string[start]) % MOD_NUM;

        /*std::cout << "Rolling hash calculation  " <<  hash_string[start - CHUNK_SIZE] << 
                "   " << hash_string[start] << "\n";*/

        if (new_hash < 0)
            new_hash += MOD_NUM;
        
        //std::cout << "Hash value    " << new_hash << "\n";

        previous_hash = new_hash;
        start++;
    }
}

void RollingHash::storeRollingHash(std::string& hash_string, std::unordered_map<long long, int>& hash_map)
{
    int pos = 0;
    int string_size = hash_string.size();
    long long hash_val = 0;

    while (pos <= string_size - CHUNK_SIZE) {

        calculateRollingHash(hash_string, hash_val, pos + CHUNK_SIZE - 1 , pos + CHUNK_SIZE - 1);
        hash_map[hash_val] = pos;
        pos++;
    }

    /*for (auto x : hash_map)
    {
        std::cout << "Hash value    " << x.first << "\n";
    }*/
    
}

long long RollingHash::powerOfBase(int power)
{
    long long res = 1;
    int i = 0;

    while (i < power) {
        res *= BASE_NUM;
        res %= MOD_NUM;
        i++;
    }

    return res;
}