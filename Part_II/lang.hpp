#ifndef LANG_H
#define LANG_H

#include "../Part_I/fcm.hpp"
#include <vector>
#include <iostream>

using namespace std;

class lang
{
    private:
        /**
         * @brief FCM object to be used by this class
         */
        fcm fcmObj;

        /**
         * @brief Order of the finite-context model
         */
        int k;

        /**
         * @brief Smoothing parameter of the finite-context model
         */
        double alpha;

    public:
        lang();

        /**
         * Lang class constructor
         * @param k order of the finite-context model
         * @param alpha smoothing parameter of the finite-context model
         */
        lang(int k, double alpha);

        /**
         * @brief Function that compares a certain text file to a language and estimates the number
         * of bits needed to compress the text file using the language
         * @param filename path of text file to be analyzed
         * @param classFilename path of the text file that contains either the language text or the language model to be compared to
         * @param typeOfComp type of comparison to be made ('F' for file, 'M' for existing model)
         * @return estimated number of bits needed to compress the text file using the language
         */
        double estimateBits(char *filename, char *classFilename, char typeOfComp);
};

#endif