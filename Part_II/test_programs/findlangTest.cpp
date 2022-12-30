#include "../findlang.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "ERROR: Must provide at least one text file and one language/model file!\n"
             << "Usage: ./findlangTest <text_filepath> <language_filepath1> [<language_filepath2> ....]\n"
             << endl;
        return 1;
    }

    findlang::printMenu();

    while (true)
    {
        cout << ">>> ";

        string s;
        getline(cin, s);
        char op = s.at(0);

        if (s.length() > 1)
        {
            cout << "Invalid option, please try again\n"
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

            // Get filepaths of language files to be compared to
            vector<string> languages;
            for (int i = 2; i < argc; i++)
            {
                languages.push_back(argv[i]);
            }

            try
            {
                findlang findlangObj(k, alpha);
                string closest = findlangObj.estimateLanguage(argv[1], languages, 'F');

                cout << "\n*****************************************************************************\n"
                     << "\n Closest language to text is: " << closest << "\n"
                     << "\n*****************************************************************************\n"
                     << endl;

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
            // Get filepaths of language files to be compared to
            vector<string> languages;
            for (int i = 2; i < argc; i++)
            {
                languages.push_back(argv[i]);
            }

            try
            {
                findlang findlangObj;
                string closest = findlangObj.estimateLanguage(argv[1], languages, 'M');

                cout << "\n*******************************************************************************************************"
                     << "\nClosest language to text is " << closest
                     << "\n*******************************************************************************************************"
                     << endl;

                return 0;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                return 1;
            }
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