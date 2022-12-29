#include "../Part_I/fcm.cpp"
#include "lang.hpp"

using namespace std;

lang::lang()
{
    this->fcmObj = fcm();
}

lang::lang(int k, double alpha)
{
    this->k = k;
    this->alpha = alpha;
    this->fcmObj = fcm(k, alpha);
}

double lang::estimateBits(char *filename, char *classFilename, char typeOfComp)
{
    // Empty model that will be filled with the model of the language
    map<string, map<char, int>> languageModel;

    // If comparing to a file, generate the model for the language file, using the FCM methods developed in Part_I, and save it in the empty model
    if (typeOfComp == 'F')
    {
        this->fcmObj.loadModel(classFilename, 'N', &languageModel);
    }
    // If comparing to an existing model, read the model from the model file, using the FCM methods developed in Part_I, and save it in the empty model
    else
    {
        this->fcmObj.readModel(classFilename, languageModel, this->k, this->alpha);
    }

    // Open the text file to be analysed
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        throw invalid_argument("\nERROR: Could not open file: " + string(filename) + "\nCheck if the file exists and the path is correct\n");
    }

    // Check if file is empty
    if (ifs.peek() == ifstream::traits_type::eof())
    {
        throw invalid_argument("\nERROR: " + string(filename) + " is an empty file! \nPlease use a valid text file\n");
    }

    // Print message according to type of comparison
    if (typeOfComp == 'M')
    {
        cout << "\n-----------------------------------------------------------------------------\n"
             << "Comparing the text with the obtained language model\n"
             << endl;
    }
    else
    {
        cout << "Comparing the text with the obtained language model\n"
             << endl;
    }

    // Initialize context according to order k
    string context = "";
    char nextChar;
    for (int i = 0; i < this->k; i++)
    {
        fcm::readChar(ifs, &nextChar);
        context += nextChar;
    }

    // Read text file and compare with language model
    double estimatedEntropy = 0;
    int totalFileChars = 0;

    while (!ifs.eof() && ifs.good())
    {
        int num = 0;
        int totalNum = 0;

        fcm::readChar(ifs, &nextChar);

        // Count total number of chars in file
        totalFileChars++;

        if (languageModel.count(context) > 0)
        {
            // Count total number of next character occurrences in this context
            totalNum = accumulate(languageModel[context].begin(), languageModel[context].end(), 0, [](int sum, pair<char, int> p)
                                  { return sum + p.second; });

            // Check if nextChar exists in this context
            if (languageModel[context].count(nextChar) > 0)
            {
                num = languageModel[context][nextChar];
            }
        }

        // Add entropy to total estimated entropy
        estimatedEntropy += -log2((num + this->alpha) / (totalNum + (this->alpha * ALPHABET_SIZE)));

        // Update context by removing its first char and appending next char
        context = context.substr(1, this->k - 1) + nextChar;
    }
    ifs.close();

    cout << "Estimated number of bits to compress text: " << estimatedEntropy
         << "\nEstimated number of bits per character: " << estimatedEntropy / totalFileChars
         << "\n-----------------------------------------------------------------------------"
         << endl;

    return estimatedEntropy;
}