#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <limits>
#include <map>

enum Difficulty{
    Easy=1,
    Medium,
    Hard
};
std::map<Difficulty, int> difficultyChances = {
    {Easy, 10},
    {Medium, 5},
    {Hard, 3}
};


const int MIN_NUMBER=1;
const int MAX_NUMBER=100;

void PrintBeginningMessage();
void GetChoice(Difficulty choice, int& chances, bool& validChoice);
void CheckGuess(const int randomNum, const int guess, int& chances, int& attempts, bool& correctGuess);
void GetQuitChoice(bool& validQuitChoice, bool& quitting, const std::string quitChoice);
void GameplayLoop(bool& quitting);

int main(){
    srand(time(0));
    bool quitting=false;
    while(!quitting){
        GameplayLoop(quitting);
    }
}

void GameplayLoop(bool& quitting){
    int randomNum = (rand()%MAX_NUMBER)+MIN_NUMBER;
    int attempts = 0;
    int choice = 0;
    int chances = 0;
    int guess=101;
    bool correctGuess=false;
    bool validChoice=false;
    std::string quitChoice="x";

    while (!validChoice)
    {
        PrintBeginningMessage();
        std::cin>>choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        GetChoice(static_cast<Difficulty>(choice),chances,validChoice);
    }
    while((!correctGuess) && (chances>0)){
        std::cout<<"Enter your guess: ";
        std::cin>>guess;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        CheckGuess(randomNum, guess, chances, attempts, correctGuess);
    }


    bool validQuitChoice=false;
    while(!validQuitChoice){
        std::cout<<"Would you like to continue playing?(y/n): ";
        std::cin>>quitChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::transform(quitChoice.begin(), quitChoice.end(), quitChoice.begin(), ::toupper);
        
        GetQuitChoice(validQuitChoice,quitting,quitChoice);
    }
}

void PrintBeginningMessage(){
    std::cout<<"Welcome to the number guessing game!"<<std::endl
             <<"I'm thinking of a number between 1 and 100"<<std::endl
             <<"Depending on the difficulty you'll have a few chances to figure out the number"<<std::endl
             <<std::endl
             <<"Please select difficulty level:"<<std::endl
             <<"1. Easy ("<<difficultyChances[Easy]<<" chances)"<<std::endl
             <<"2. Medium ("<<difficultyChances[Medium]<<" chances)"<<std::endl
             <<"3. Hard ("<<difficultyChances[Hard]<<" chances)"<<std::endl
             <<std::endl
             <<"Enter your choice: ";
}

void GetChoice(Difficulty choice, int& chances, bool& validChoice){

    if (choice!=Easy&&choice!=Medium&&choice!=Hard){
        std::cout<<"ERROR: Choose a valid difficulty"<<std::endl;
        validChoice=false;
        std::cin.get();
    }
    else{
        chances = difficultyChances[choice];
        std::cout<<"You have selected the Easy difficulty ("<<difficultyChances[choice]<<" chances)"<<std::endl;
        validChoice=true;
    }

}

void CheckGuess(const int randomNum, const int guess, int& chances, int& attempts, bool& correctGuess){
    if (guess<MIN_NUMBER || guess>MAX_NUMBER){
            std::cout<<"ERROR: guess not valid"<<std::endl;
            std::cin.get();
            return;
        }

    if(randomNum<guess){
        std::cout<<"The number is smaller than "<<guess<<std::endl;
        chances-=1;
        attempts+=1;
        std::cout<<"You have "<<chances<<" chances left"<<std::endl<<std::endl;
    }
    else if (randomNum>guess){
        std::cout<<"The number is bigger than "<<guess<<std::endl;
        chances-=1;
        attempts+=1;
        std::cout<<"You have "<<chances<<" chances left"<<std::endl<<std::endl;
    }
    else{
        std::cout<<std::endl<<"Congratulations! You have guessed the number in "<<attempts<<" attempts!"<<std::endl;
        correctGuess=true;
    }
    if (chances==0){
        std::cout<<std::endl<<"You lost! The number was "<<randomNum<<std::endl;
    }
}

void GetQuitChoice(bool& validQuitChoice, bool& quitting, const std::string quitChoice){
    if(quitChoice=="Y"||quitChoice=="YES"){
        quitting=false;
        validQuitChoice=true;
    }
    else if(quitChoice=="N"||quitChoice=="NO"){
        quitting=true;
        validQuitChoice=true;
    }
    else{
        std::cout<<"ERROR: Choice not valid"<<std::endl;
        validQuitChoice=false;
    }
}

