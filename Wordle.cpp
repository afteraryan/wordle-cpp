#include<iostream>
#include<string>
#include<cstring>
#include <conio.h>
#include<windows.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include<time.h>
#include<stdlib.h>

const int LetterLimit = 5;

using namespace std;

int arrAlphabetFlag[26];


void AlphabetFlagFunc()
{
    for(int i=0 ;i<26 ;i++)
    {
        arrAlphabetFlag[i]=-1;
    }
}



void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

string inputUser(string str, vector<string> validWords)
{
    

    while (1)
    {
        cout<<"\nEnter String: ";
        std::getline(cin,str);
        if(str.length()==LetterLimit)
        {
            std::transform(str.begin(), str.end(),str.begin(), ::toupper);
            if (std::count(validWords.begin(), validWords.end(), str)) 
            {
                std::cout << "Element found";
                break;
            }
            else
            cout<<"Invalid Word!";
        }    
        else
            cout<<"Letter Count = "<<LetterLimit<<"!";
    }
    
    return str;
}

bool checkSameWord(string answerStr, string userStr)
{
    return(answerStr==userStr);
}

void KeyboardManager(string userStr, vector<int> arrFlag)
{
    std::vector<char> Alphabet;
    {
        Alphabet.push_back('Q');    Alphabet.push_back('W');    Alphabet.push_back('E');    Alphabet.push_back('R');    Alphabet.push_back('T');
        Alphabet.push_back('Y');    Alphabet.push_back('U');    Alphabet.push_back('I');    Alphabet.push_back('O');    Alphabet.push_back('P');
        Alphabet.push_back('A');    Alphabet.push_back('S');    Alphabet.push_back('D');    Alphabet.push_back('F');    Alphabet.push_back('G');
        Alphabet.push_back('H');    Alphabet.push_back('J');    Alphabet.push_back('K');    Alphabet.push_back('L');    Alphabet.push_back('Z');
        Alphabet.push_back('X');    Alphabet.push_back('C');    Alphabet.push_back('V');    Alphabet.push_back('B');    Alphabet.push_back('N');
        Alphabet.push_back('M');
    }
        

    for(int i=0; i<5;i++)
    {
        for(int j=0; j<26;j++)
        {
            if (userStr[i]==Alphabet[j])
            {
                if(arrAlphabetFlag[j]!=1)
                {
                    if(arrAlphabetFlag[j]!=2 || (arrAlphabetFlag[j]==2 && arrFlag[i]==1))
                        arrAlphabetFlag[j]=arrFlag[i];
                }
            }

        }
    }

    

    cout << endl;
    for (int i = 0; i < 26; i++)
    {
        if(arrAlphabetFlag[i]==0)
        {
            textcolor(0);//Grey
            cout<<Alphabet[i]<<" ";
        }
        else if(arrAlphabetFlag[i]==2)
        {
            textcolor(6);//Yellow
            cout<<Alphabet[i]<<" ";
        }
        else if(arrAlphabetFlag[i]==1)
        {
            textcolor(10);//Green
            cout<<Alphabet[i]<<" ";
        }  
        else if(arrAlphabetFlag[i]==-1)
        {
            textcolor(7);//White
            cout<<Alphabet[i]<<" ";
        } 
        if(i==9)
        cout<<"\n ";
        if(i==18)
        cout<<"\n  ";

    }
    textcolor(7);
    cout << endl;
}

void OutputManager(string userStr, vector<int> arrFlagX)
{
    for(int i=0; i<5; i++)
    {
        if(arrFlagX[i]==0)
        {
            textcolor(4);//Red
            cout<<userStr[i];
        }
        else if(arrFlagX[i]==2)
        {
            textcolor(6);//Yellow
            cout<<userStr[i];
        }
        else if(arrFlagX[i]==1)
        {
            textcolor(10);//Green
            cout<<userStr[i];
        }
        else
        {
            textcolor(7);//White
            cout<<userStr[i];
        }
    }
    textcolor(7);//White
    cout<<endl;
}

vector<int> MasterChecker(string answerStr, string userStr, vector<int> arrFlagX)
{
    
    bool arrIsClue[5] = {false, false, false, false};
    
    for(int i = 0; i<LetterLimit; i++)
    {
            arrFlagX[i]=0;        
    }

    for(int i = 0; i<LetterLimit; i++)
    {
        if(answerStr[i]==userStr[i])
        {
            arrFlagX[i]=1; // '1' acts as a Flag
            arrIsClue[i]=true;          
        } 
    }

    //Similar Leters
    for(int i=0; i<LetterLimit; i++)
    {
        if(arrFlagX[i]==0)
        {
            for(int j=0; j<LetterLimit; j++)
            {
                if(((userStr[i]==answerStr[j]) && (i!=j)) && !arrIsClue[j])
                {
                    arrFlagX[i] = 2;
                    arrIsClue[j] = true;
                    //break;
                }  
            }
        }
            
    }
    KeyboardManager(userStr, arrFlagX);
    //Output
    //OutputManager(userStr, arrFlagX);
    return arrFlagX;
}

void ReadFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();
}

int RandomInt(int VectorLength)
{
    srand((unsigned int)time(NULL));
    float a = VectorLength;
    return (int)(float(rand())/float((RAND_MAX)) * a);
}



int main()
{
    
    string userStr, answerStr = "AGREE", outputStr;
    int triesAvailable=6;  
    std::vector<std::string> InputList = {"-----", "-----", "-----", "-----", "-----", "-----"};
    
    //File Reading
    std::vector<std::string> vecOfStr;
    ReadFileContent("Words.txt", vecOfStr);

    std::vector<std::string> validWords;
    ReadFileContent("ValidWords.txt", validWords);

    std::vector<vector<int>> arrFlag = {{7,7,7,7,7},{7,7,7,7,7},{7,7,7,7,7},{7,7,7,7,7},{7,7,7,7,7},{7,7,7,7,7}};


    answerStr = vecOfStr[RandomInt(vecOfStr.size())];
    std::transform(answerStr.begin(), answerStr.end(),answerStr.begin(), ::toupper);

    
    AlphabetFlagFunc();
    for(int j=0; j<6; j++)
    {
        cout<<InputList[j]<<endl;
    }


    //6 Tries
    while(triesAvailable>0)
    {
        triesAvailable--;
        //cout<<"\n\nTry Number: "<<6-triesAvailable<<endl;
        userStr = inputUser(userStr, validWords);
        InputList[6-triesAvailable-1] = userStr;
        
        system("CLS");

        

        if(checkSameWord(answerStr, userStr))
        {
            cout<<"Right Answer!!";
            break;
        }
        else   
           arrFlag[6-triesAvailable-1] = MasterChecker(answerStr, userStr, arrFlag[6-triesAvailable-1]);
        
        cout<<"\n\n";
        for(int j=0; j<6; j++)
        {
            //cout<<InputList[j]<<endl;
            OutputManager(InputList[j], arrFlag[j]);
        }
    }


    return 0;
}


