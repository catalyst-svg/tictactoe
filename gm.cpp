#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
 
class player
{
    const std::string m_name;
public:
    player(const std::string name)
        :m_name(name)
    {}
    void getName() const
    {
        std::cout << m_name;
    }
};
 
class board
{
public:
    static std::vector<std::vector<char>> board1;
    static void printBoard()
    {
        for (auto i{0}; i < (int)board1.size(); i++)
        {
            for (auto x{0}; x < (int)board1[i].size(); x++)
            {
                std::cout << std::setw(2) << board1[i][x];
                if (x < (int)board1[i].size() - 1)  // fixed: board1[i] not board1[x]
                {
                    std::cout << std::setw(2) << "|";
                }
            }
            std::cout << std::endl;
            if (i < (int)board1.size() - 1)  // don't print divider after last row
            {
                std::cout << "---+---+---" << std::endl;
            }
        }
    }
    static void placement(int userRow, int userCol, char userS)
    {
        if (board1[userRow - 1][userCol - 1] == '.')  // '.' as empty cell
        {
            board1[userRow - 1][userCol - 1] = userS;
        }
        else
        {
            std::cout << "Already A Value Placed In That Square!" << std::endl;
        }
    }
};
 
std::vector<std::vector<char>> board::board1 = {{'.','.','.',},
                                                 {'.','.','.',},
                                                 {'.','.','.'}};
 
class game
{
public:
    static bool play1;
    static bool turnManager()
    {
        if (play1)
        {
            play1 = false;
            return true;
        }
        else
        {
            play1 = true;
        }
        return false;
    }
 
    static bool winChecker(std::vector<std::vector<char>>& gameBoard, int rowChose, int colChose)
    {
        bool rowTrue{true}, colTrue{true}, dLTrue{true}, dRTrue{true};
 
        // Row check
        char rowVal = gameBoard[rowChose][0];
        if (rowVal == '.') rowTrue = false;  // empty cells can't win
        for (auto& val : gameBoard[rowChose])
        {
            if (val != rowVal)
            {
                rowTrue = false;
            }
        }
 
        // Column check
        char colVal = gameBoard[0][colChose];
        if (colVal == '.') colTrue = false;  // empty cells can't win
        for (auto& row : gameBoard)
        {
            if (row[colChose] != colVal)
            {
                colTrue = false;
            }
        }
 
        // Left to right diagonal check
        char leftToRightVal = gameBoard[0][0];
        if (leftToRightVal == '.') dLTrue = false;  // empty cells can't win
        int valTracker{0};
        for (auto row{0}; row < (int)gameBoard.size(); row++)
        {
            if (gameBoard[row][valTracker] != leftToRightVal)
            {
                dLTrue = false;
            }
            valTracker++;
        }
 
        // Right to left diagonal check
        char rightToLeftVal = gameBoard[0][2];
        if (rightToLeftVal == '.') dRTrue = false;  // empty cells can't win
        valTracker = 2;
        for (auto row{0}; row < (int)gameBoard.size(); row++)
        {
            if (gameBoard[row][valTracker] != rightToLeftVal)
            {
                dRTrue = false;
            }
            valTracker--;
        }
 
        return rowTrue || colTrue || dLTrue || dRTrue;
    }
};
 
bool game::play1 = true;
 
int main()
{
    const char p1S{'X'};
    const char p2S{'O'};  // fixed: was 'Y'
    std::string name;
    bool whichTurn;
    bool isWinner;
    int r{};
    int c{};
 
    std::cout << "   TIC-TAC-TOE\n";
    std::cout << "------------------" << std::endl;
    std::cout << "PLAYER 1 NAME: ";
    std::getline(std::cin, name);
    player p1(name);
    std::cout << "PLAYER 2 NAME: ";
    std::getline(std::cin, name);
    player p2(name);
 
    while(true)
    {
        std::cout << "\033[2J\033[H";  // clear terminal
        whichTurn = game::turnManager();
        if (whichTurn)
        {
            board::printBoard();
            p1.getName();
            std::cout << " - Choose Row: ";
            std::cin >> r;
            std::cout << "Choose Column: ";
            std::cin >> c;
            board::placement(r, c, p1S);
            isWinner = game::winChecker(board::board1, r - 1, c - 1);
            if (isWinner)
            {
                std::cout << "\033[2J\033[H";
                board::printBoard();
                p1.getName();
                std::cout << " is the Winner!!!" << std::endl;
                break;
            }
        }
        else
        {
            board::printBoard();
            p2.getName();
            std::cout << " - Choose Row: ";
            std::cin >> r;
            std::cout << "Choose Column: ";
            std::cin >> c;
            board::placement(r, c, p2S);
            isWinner = game::winChecker(board::board1, r - 1, c - 1);
            if (isWinner)
            {
                std::cout << "\033[2J\033[H";
                board::printBoard();
                p2.getName();
                std::cout << " is the Winner!!!" << std::endl;
                break;
            }
        }
    }
 
    return 0;
}
