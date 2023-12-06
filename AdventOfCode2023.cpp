// AdventOfCode2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> digitSpelled = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

void day1();

void day2();

int main()
{
    int day;
    cout << "Which day do you want to run?\n";
    cin >> day;
    
    switch (day)
    {
    case 1:
        day1();
        break;
    case 2:
        day2();
        break;
    default:
        break;
    }

    return 0;
}

// Create a method day1 that returns a string
void day1()
{
    cout << "Day 1\n";
    // read day1.txt file into string array
    vector<string> lines;
    const char* fileName = "day1.txt";
    ifstream file(fileName);
    string s;
    while (getline(file, s))
    {
        lines.push_back(s);
    }

    int sum = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        // Get the line at index i from lines
        string line = lines[i];
        int firstDigit;
        try {
            size_t firstDigitIndex = line.find_first_of("0123456789");

            size_t firstDigitSpelledIndex;
            int firstSpelledDigit;
            for (int j = 0; j < digitSpelled.size(); j++)
            {
				firstDigitSpelledIndex = line.find(digitSpelled[j]);
                firstSpelledDigit = j;
			}

            bool firstDigitIsSpelled = firstDigitSpelledIndex < firstDigitIndex;

            if (firstDigitIsSpelled) {
                firstDigit = firstSpelledDigit;
            }
            else {
                char firstDigitChar = line[firstDigitIndex];
                // Convert the first digit to an int
                firstDigit = stoi(string(1, firstDigitChar));
            }
        }
        catch (exception e) {
            cout << "Failed at firstDigit: " << i << "\n";
            break;
        }
        int lastDigit;
        try {
            size_t lastDigitIndex = line.find_last_of("0123456789");

            size_t lastDigitSpelledIndex = 0;
            size_t previousLastDigitSpelledIndex = 0;
            int lastSpelledDigit;
            for (int j = 0; j < digitSpelled.size(); j++)
            {
                previousLastDigitSpelledIndex = lastDigitSpelledIndex;
                
                lastDigitSpelledIndex = line.find(digitSpelled[j]);
                if (lastDigitSpelledIndex != previousLastDigitSpelledIndex) {
                    if (i == 3)
                    {

                    }
                    lastSpelledDigit = j;
                }
            }

            bool lastDigitIsSpelled = lastDigitSpelledIndex < lastDigitIndex;

            if (lastDigitIsSpelled) {
                lastDigit = lastSpelledDigit;
            }
            else {
                char lastDigitChar = line[lastDigitIsSpelled ? lastDigitSpelledIndex : lastDigitIndex];

                // Convert the last digit to an int
                lastDigit = stoi(string(1, lastDigitChar));
            }
        }
        catch (exception e)
        {
            cout << "Failed at lastDigit: " << i << "\n";
            cout << e.what() << "\n";
            break;
        }
        int number = firstDigit * 10 + lastDigit;

        // Add number to sum
        sum += number;
	}
	cout << "Sum: " << sum << endl;
}

void day2() {
    cout << "Day 2\n";

    // read day2.txt file into string array
    vector<string> games;
    const char* fileName = "day2.txt";
    ifstream file(fileName);
    string s;
    while (getline(file, s))
    {
        games.push_back(s);
    }

    int sum = 0;
    for (int index = 0; index < games.size(); index++) {
        int gameId = index + 1;
        string game = games[index];
        bool gameIsValid = true;
        // Replace all semicolons with commas
        size_t semicolonIndex = game.find(";");
        while (semicolonIndex != string::npos) {
			game.replace(semicolonIndex, 1, ",");
			semicolonIndex = game.find(";");
		}

        size_t gamePos = 0;
        gamePos = game.find("Game");
        game.erase(gamePos, gameId < 10 ? 7 : gameId < 100 ? 8 : 9);

        size_t pos = 0;

        while ((pos = game.find(",")) != string::npos) {
			string cubes = game.substr(0, pos);
			game.erase(0, pos + 1);
            if (cubes.find("red") != string::npos) {
                // Remove "red" from cubes
                cubes.erase(cubes.find("red"), 3);
                
                // Convert cubes to int
                int cubesInt = stoi(cubes);
                
                if (cubesInt > 12) {
                    gameIsValid = false;
                    break;
                }
            }
            else if (cubes.find("blue") != string::npos) {
				// Remove "blue" from cubes
				cubes.erase(cubes.find("blue"), 4);
				// Convert cubes to int
				int cubesInt = stoi(cubes);
                
                if (cubesInt > 14) {
                    gameIsValid = false;
                    break;
                }
			}
            else if (cubes.find("green") != string::npos) {
				// Remove "green" from cubes
				cubes.erase(cubes.find("green"), 5);
				// Convert cubes to int
				int cubesInt = stoi(cubes);
				
                if (cubesInt > 13) {
                    gameIsValid = false;
                    break;
                }
            }
		}

    

        if (gameIsValid) {
            cout << gameId << " Yes\n";
            sum += gameId;
        }
        else
        {
            cout << gameId << " No\n";
        }
        cout << "Sum after game " << gameId << ":" << sum << endl;
    }
    cout << "Sum: " << sum << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
