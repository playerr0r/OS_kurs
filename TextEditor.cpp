#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

const int numMenuItems = 6;
int menuItem = 0;
std::string menuArray[numMenuItems]{ "add new file","text output","text editing","highlight numbers","search for matches","exit" };

enum
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_ENTER = 13,
    KEY_ESC = 27,
    KEY_BACKSPACE = 8
};

char fileName[100];
std::string* text;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void name()
{
    std::cout << "write name of your file" << std::endl;
    memset(fileName, 0, 100);
    std::cin >> fileName;
}

void newFile()
{
    system("cls");
    name();
    char newText[1000];

    std::ofstream newFile;
    newFile.open(fileName);
    if (newFile.is_open())
    {
        std::cout << "write your text" << std::endl;
        std::cin.ignore();
        std::cin.getline(newText, 1000);
        newFile << newText;
    }
    else
        std::cout << "you can't create new file";

    newFile.close();
}

void existingFile()
{
    system("cls");
    name();
}

int CountLinesInFile()
{
    int linesCount = 0;
    char buffer[1000];

    std::ifstream file;
    file.open(fileName);

    if (file.is_open())
    {
        while (!file.eof())
        {
            linesCount++;
            file.getline(buffer, 1000);
        }
    }
    else
        std::cout << "you can't open this file";

    file.close();
    return linesCount;
}

void textReading()
{
    system("cls");

    int size = CountLinesInFile();
    text = new std::string[size];
    char buffer[1000];

    std::ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            file.getline(buffer, 1000);

            int length;
            for (length = 0; buffer[length] != '\0'; length++);
            text[i].assign(buffer, length);
        }
        std::cout << "\nfile added successfully\n\n";
    }
    else
        std::cout << "you can't read this file";

    file.close();
    std::cout << "\n\npress enter to leave\n\n";
    std::cin.ignore();
    std::cin.get();
}

void addFile()
{
    system("cls");

    std::cout << "if you want to open an existing file write 1\nif you want to create a new file write 2\n";
    int choose;
    std::cin >> choose;
    if (choose == 1)
        existingFile();
    else if (choose == 2)
        newFile();
    textReading();
}

void textOutput()
{
    system("cls");

    int size = CountLinesInFile();
    for (int i = 0; i < size; i++)
    {
        std::cout << text[i] << std::endl;
    }

    std::cout << "\n\npress enter to leave\n\n";
    std::cin.get();
}

void addString(int y, int x)
{
    for (;;)
    {
        text[y].append(1, '\n');
        break;
    }
    system("cls");
    int size = CountLinesInFile();
    for (int i = 0; i < size; i++)
    {
        std::cout << text[i] << std::endl;
    }
    std::cout << "\n\npress esc to leave";
    return;
}

void eraseChar(int y, int x)
{
    for (;;)
    {
        text[y].erase(x, 1);
        break;
    }
    system("cls");
    int size = CountLinesInFile();
    for (int i = 0; i < size; i++)
    {
        std::cout << text[i] << std::endl;
    }
    std::cout << "\n\npress esc to leave";
}

void textEditing()
{
    system("cls");

    int size = CountLinesInFile();
    for (int i = 0; i < size; i++)
    {
        std::cout << text[i] << std::endl;
    }
    std::cout << "\n\npress esc to leave";

    COORD coordinates;
    int x = 0, y = 0;
    while (_getch() != KEY_ESC)
    {
        coordinates.X = x;
        coordinates.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

        switch (_getch())
        {
        case KEY_UP: y--;                   break;
        case KEY_DOWN: y++;                 break;
        case KEY_LEFT: x--;                 break;
        case KEY_RIGHT: x++;                break;
        case KEY_BACKSPACE: eraseChar(y, x);      break;
        case KEY_ENTER: addString(y, x);    break;
        }
    }
}

void highlightNumbers()
{
    system("cls");

    const int initialLimit = 47;
    const int finiteLimit = 58;
    int size = CountLinesInFile();
    for (int i = 0; i < size; i++)
    {
        int stringLenght = text[i].length();
        for (int j = 0; j < stringLenght; j++)
        {
            if (text[i][j] > initialLimit && text[i][j] < finiteLimit)
            {
                SetConsoleTextAttribute(hConsole, (WORD)((9 << 4) | 7));
                std::cout << text[i][j];
                SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
            }
            else
            {
                std::cout << text[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\npress enter to leave\n\n";
    std::cin.get();
}

void searchForMatches()
{
    system("cls");

    int size = CountLinesInFile();
    std::string searchText;
    std::cout << "write the text that you searching:\n";
    std::cin >> searchText;
    int searchTextLenght = searchText.length();

    system("cls");
    for (int i = 0; i < size; i++)
    {
        int stringLenght = text[i].length();
        int position = text[i].find(searchText);

        for (int j = 0; j < stringLenght; j++)
        {
            if (position != std::string::npos && position == j)
            {
                int count = 0;
                while (count < searchTextLenght)
                {
                    SetConsoleTextAttribute(hConsole, (WORD)((6 << 4) | 7));
                    std::cout << text[i][j];
                    SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
                    count++;
                    j++;
                }
                j--;
            }
            else
            {
                std::cout << text[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\npress enter to leave\n\n";
    std::cin.ignore();
    std::cin.get();
}

// MENU PART

void windows(int menuItem)
{
    switch (menuItem)
    {
    case 0:
        addFile();
        break;
    case 1:
        textOutput();
        break;
    case 2:
        textEditing();
        break;
    case 3:
        highlightNumbers();
        break;
    case 4:
        searchForMatches();
        break;
    case 5:
        exit(1);
        break;
    }
}

void keys(int ch)
{
    switch (ch)
    {
    case KEY_ESC: exit(1);
    case KEY_UP: menuItem--;            break;
    case KEY_DOWN: menuItem++;          break;
    case KEY_ENTER:
        windows(menuItem);              break;
    }
}

int main()
{
    bool ext = false;
    while (!ext)
    {
        system("cls");

        if (menuItem < 0) menuItem = numMenuItems - 1;
        if (menuItem > numMenuItems - 1) menuItem = 0;

        for (int i = 0; i < numMenuItems; i++)
        {
            if (menuItem == i) std::cout << "-";
            std::cout << menuArray[i];
            if (menuItem == i) std::cout << "-";
            std::cout << std::endl;
        }
        keys(_getch());
    }
}