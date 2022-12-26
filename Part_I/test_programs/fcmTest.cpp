#include "../fcm.hpp"
#include "../fcm.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc !=4 ) 
    {
        cerr << "ERROR: Usage: ./fcmTest <filename> <order k> <smoothing parameter>\n" << endl;
        return 1;
    }

    if(!fcm::isInteger(argv[2]) || stoi(argv[2]) <= 0)
    {
        cerr << "ERROR! Model order k must be a valid positive integer\n" 
            << "USAGE: ./fcmTest <filename> <order k> <smoothing parameter>\n"
            << endl;
        return 1;
    }

    if(!fcm::isDecimal(argv[3]) || stod(argv[3]) <= 0)
    {
        cerr << "ERROR! Smoothing parameter must be a valid positive number\n" 
            << "USAGE: ./fcmTest <filename> <order k> <smoothing parameter>\n" 
            << endl;
        return 1;
    }

    cout << "-----------------------------------TEST FCM-----------------------------------\n"
        << "Order k = " << stoi(argv[2]) 
        << "\nSmoothing parameter alpha = " << stod(argv[3]) << "\n\n"
        << "Please choose an option:\n"
        << "[1]: analyse file and save model in memory\n" 
        << "[2]: analyse file without saving model\n" 
        << "[q]: exit\n" 
        << endl;

    while(true)
    {
        char op = 0;
        cout << ">>> ";
        cin >> op;

        switch (op)
        {
            case '1':
            {
                fcm fcm(stoi(argv[2]), stod(argv[3]));
                fcm.estimateFileEntropy(argv[1], 'Y');
                return 0;
            }
            case '2':
            {
                fcm fcm(stoi(argv[2]), stod(argv[3]));
                fcm.estimateFileEntropy(argv[1], 'N');
                return 0;
            }
            case 'q':
            {
                cout << "\nLeaving program, goodbye!\n" << endl;
                return 0;
            }
            default:
            {
                cout << "Invalid option, please try again\n" << endl;
                break;
            }
        }
    }
    return 0;
}