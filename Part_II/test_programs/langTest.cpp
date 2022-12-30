#include "../lang.cpp"
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "\nERROR: Incorrect number of arguments!\n"
             << "\nUsage: ./langTest <text_filepath> <language_filepath>\n"
             << endl;
        return 1;
    }

    cout << "\nWhich type of file are you using to represent the language?\n"
         << "[1] text file\n"
         << "[2] model file\n"
         << "[q] quit\n"
         << endl;

    while (true)
    {
        cout << ">>> ";

        string s;
        getline(cin, s);
        char op = s.at(0);

        if (s.length() > 1)
        {
            cout << "\nInvalid option, please try again\n"
                 << endl;
            continue;
        }

        else if (op == '1')
        {
            // Get value of model order k
            cout << "\nValue of model order: ";
            string ord;
            getline(cin, ord);

            if (!fcm::isInteger(ord) || stoi(ord) <= 0)
            {
                cerr << "\nERROR! Model order k must be a valid positive integer\n"
                     << endl;
                return 1;
            }
            int k = stoi(ord);

            // Get value of smoothing parameter alpha
            cout << "\nValue of smoothing parameter: ";
            string alp;
            getline(cin, alp);

            if (!fcm::isDecimal(alp) || stod(alp) <= 0)
            {
                cerr << "\nERROR! Smoothing parameter must be a valid positive number\n"
                     << endl;
                return 1;
            }
            double alpha = stod(alp);

            // Perform analysis
            try
            {
                lang langObj(stoi(ord), stod(alp));
                langObj.estimateBits(argv[1], argv[2], 'F');
                return 0;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                return 1;
            }
        }

        else if (op == '2')
        {
            // Perform analysis
            try
            {
                lang langObj;
                langObj.estimateBits(argv[1], argv[2], 'M');
                return 0;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                return 1;
            }
            return 0;
        }

        else if (op == 'q')
        {
            cout << "\nLeaving program, goodbye!\n"
                 << endl;
            return 0;
        }

        else
        {
            cout << "\nInvalid option, please try again\n"
                 << endl;
            continue;
        }
    }
    return 0;
}