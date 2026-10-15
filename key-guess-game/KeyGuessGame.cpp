#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <utility>

int isPresent(int target, const std::vector<int>& vec){
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end())
        return it - vec.begin();
    return -1;
}

std::vector<int> genKey(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(0,9);

    std::vector<int> key;

    while (key.size() < 4){
        int digit = distrib(gen);
        auto inKey = std::find(key.begin(), key.end(), digit);
        if (inKey == key.end())
            key.push_back(digit);
    }

    return key;
}

bool isValid(const std::string& userKey){
    if (userKey.length() != 4) return false;

    std::unordered_set<char> seen;

    for (char ch: userKey){
        if (!isdigit(ch) || !seen.insert(ch).second)
            return false;
    }
    return true;
}

std::vector<int> toVector(const std::string& key){
    std::vector<int> result;
    for (char ch : key) {
        result.push_back(ch - '0');
    }
    return result;
}

std::pair<int,int> compare(std::vector<int> targetKey, std::vector<int> userKey){
    int numCtr = 0;
    int posCtr = 0;
    for (int i = 0; i < userKey.size(); i++){
        int digit = userKey[i];
        int targetIndex = isPresent(digit, targetKey);
        if (targetIndex >= 0){
            numCtr++;

            if (targetIndex == i){
                posCtr++;
            }
        }

    }
    return {numCtr, posCtr};
}

int main(){
    bool play = true;
    while (play){
        std::cout << "~~~~~ Key Guess Game ~~~~~\n"  
                  << "1. Play\n"
                  << "2. Help\n"
                  << "3. Exit\n";
        std::cout << "[ Enter choice (1,2,3) ]: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:{
                bool playRound = true;
                while (playRound) {
                    std::cout << "\nAlright ! Let's begin !\n\n";
                    std::vector<int> key = genKey();
                    int tryCtr = 0;
                    std::string userKey;
                    while (true) {
                        do {
                            std::cout << "Enter guess: ";
                            std::cin >> userKey;
                            if (!isValid(userKey)){
                                std::cout << "Not a valid key, try again\n";
                                continue;
                            }
                            else  break;
                        } while (true);
                        
                        ++tryCtr;
                            
                        if (toVector(userKey) == key) {
                            std::cout << "\nCorrect!!!\nYou took " << tryCtr << " tries!\n\n";
                            std::cout << "You wanna play another round?! (y/n): ";
                            char answer;
                            std::cin >> answer;
                            
                            if (answer != 'y' && answer != 'Y') {
                                playRound = false; 
                            }
                            break; 
                        }
                            
                        auto [numCtr, posCtr] = compare(key, toVector(userKey));
                        std::cout << "Numbers Matching:  " << numCtr << '\n' 
                                  << "Position Matching: " << posCtr << '\n'
                                  << '\n';

                    }

                }

                break;
            }

            case 2:{
                std::cout << "\nA key here is basically a 4 digit unique number.\n"
                          << "In the game, the program will generate a key.\n"
                          << "Your goal is to guess that 'key'.\n"
                          << "Enter guess keys and program will then tell you the amount of numbers matching and their positions.\n"
                          << "Use these info as hints and try to guess the actual 'key'.\n"
                          << "Good luck :) !!!\n\n";
                break;
            }

            case 3:{
                play = false;
                break;
            }
            default:
                std::cout << "\n2(Please enter a valid value)\n";
        }
    }
    return 0;
}