#include "findlang.hpp"

using namespace std;

findlang::findlang()
{
}

findlang::findlang(int k, double alpha)
{
    this->langObj = lang(k, alpha);
}

string findlang::estimateLanguage(char *filename, vector<string> languages, char typeOfComp)
{
    double bestBits = 0;
    double currentBits = 0;
    string bestLanguage = "";

    // Iterate through all languages
    for (vector<string>::iterator it = languages.begin(); it != languages.end(); ++it)
    {
        // Estimate bits for each language using the lang object and its method
        currentBits = this->langObj.estimateBits(filename, const_cast<char *>((*it).c_str()), typeOfComp);

        // If this is the first language, set the its bits as the minimum bits found so far
        if (it == languages.begin())
        {
            bestBits = currentBits;
            bestLanguage = *it;
        }
        // If the bits of the current language are lower than the minimum bits, set these as the minimum bits found so far
        else if (currentBits < bestBits)
        {
            bestBits = currentBits;
            bestLanguage = *it;
        }
    }

    // Get name of the language file that best represents the text file, without path
    bestLanguage = bestLanguage.substr(bestLanguage.find_last_of("/\\") + 1);

    return bestLanguage;
}