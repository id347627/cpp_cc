#include <iostream>
#include <string>
#include <array>
#include <time.h>

using namespace std;

const string playerSelectMsg = "Please select player type (0=Human, 1=SmartAI, 2=RandomAI):";

enum CellType {EMPTY=' ', O='O', X='X'};
enum PlayerType {Human, SmartAI, RandomAI};
enum GameStatus {InProgress, Win, Tie};

class Board{
    CellType board[3][3];
public:
    Board(){
        for(int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j ){
                board[i][j] = CellType::EMPTY;
            }
    }

    GameStatus checkStatus() {
        int sum;
        bool emptyExist = false;

        for(int i=0; i<3; i++){
            sum = 0;
            for(int j=0; j<3; j++){

                if (!emptyExist && board[i][j] == EMPTY) {emptyExist = true;}

                sum += board[i][j];
            }
            if (sum == X*3 || sum == O*3)
                return Win;
        }

        for(int j=0; j<3; j++){
            sum = 0;
            for(int i=0; i<3; i++){
                sum += board[i][j];
            }
            if (sum == X*3 || sum == O*3)
                return Win;
        }

        sum = 0;
        for(int i=0; i < 3; i++)
            sum += board[i][i];
        if (sum == X*3 || sum == O*3)
            return Win;

        sum = 0;
        for(int i=0, j=2; i < 3; i++, j--)
            sum += board[i][j];
        if (sum == X*3 || sum == O*3)
            return Win;

        if (emptyExist)
            return InProgress;
        else
            return Tie;
    }

    void updateBoard(int move,const CellType &p) {
        board[move % 3][(int) move / 3] = p;
    }

    bool validMove(int& move) const {
        return board[move % 3][(int) move / 3] == EMPTY ? true : false;
    }

    void printAvailableMoves() const {
        for(int j = 0; j < 3; ++j){
            std::cout << " "
               << (board[0][j] == EMPTY ? static_cast<char>(0+3*j+48) : static_cast<char>(board[0][j]) )
               << " | "
               << (board[1][j] == EMPTY ? static_cast<char>(1+3*j+48) : static_cast<char>(board[1][j]) )
               << " | "
               << (board[2][j] == EMPTY ? static_cast<char>(2+3*j+48) : static_cast<char>(board[2][j]) )
               << " "
               << endl;
            if(j<2){
                cout << "-----------" << endl;;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Board& b){
        for(int j = 0; j < 3; ++j){
            os << ' '
               << static_cast<char>(b.board[0][j])
               << " | "
               << static_cast<char>(b.board[1][j])
               << " | "
               << static_cast<char>(b.board[2][j])
               << ' '
               << endl;
            if(j<2){
                os << "-----------" << endl;
            }
        }
        return os;
    }

};


class Player {
protected:
    PlayerType playerType;
    CellType playerSymbol;
public:
    Player(PlayerType p, CellType s):playerType{p}, playerSymbol{s}{}
    virtual ~Player(){};
    virtual CellType& getPlayerSymbol() {return playerSymbol;}
    virtual int makeMove(const Board&) { return 0; };
    virtual char convertPlayerSymbolToChar() const{
        return static_cast<char>(playerSymbol);
    }
    friend ostream & operator<<(ostream &os, const Player& p) {
        switch(p.playerType)
            {
                case Human      : os << "Human";    break;
                case SmartAI    : os << "SmartAI";  break;
                case RandomAI   : os << "RandomAI"; break;
            }
        os << " plays with "
           << p.convertPlayerSymbolToChar();
        return os;
    }
    static Player* Create(PlayerType type, CellType c);
};

class HumanPlayer : public Player {
public:
    HumanPlayer(CellType c):Player{Human, c}{ }
    int makeMove(const Board& b) {
        int move;
        cout << "Availavle moves" << endl;
        b.printAvailableMoves();
        do {
            cout << "Player " << convertPlayerSymbolToChar() << " Make a move (1-9):";
            cin >> move;
        } while (!b.validMove(move));
         return move;
        }
};

class SmartAIPlayer : public Player {
public:
    SmartAIPlayer(CellType c):Player{SmartAI, c}{ }
    int makeMove(const Board&) { throw; return 0;}
};
class RandomAIPlayer : public Player {
    public:
    RandomAIPlayer(CellType c):Player{RandomAI, c}{ }
    int makeMove(const Board& b) {
        int move;
        do {
            move = rand() % 10;
        } while (!b.validMove(move));
        return move;
    }
};

Player* Player::Create(PlayerType type, CellType c) {
    if (type == Human)
        return new HumanPlayer(c);
    else if (type == SmartAI)
        return new SmartAIPlayer(c);
    else if (type == RandomAI)
        return new RandomAIPlayer(c);
    else return NULL;
}

class Game{
    std::array<Player*,2> players;
    Board board;
    GameStatus gameStatus;


  public:
    Game(){
        gameStatus = InProgress;
    }

    void printUserInfo(){
        for(int i =0; i<2; i++)
        cout << *players[i] << endl;
    }

    GameStatus checkGameStatus(){
        return board.checkStatus();
    }

    void startGame(){
        // select players
        int choose;
        cout << playerSelectMsg;
        cin >> choose;
        players[0] = Player::Create(static_cast<PlayerType>(choose), CellType::X);
        cout << playerSelectMsg;
        cin >> choose;
        players[1] = Player::Create(static_cast<PlayerType>(choose), CellType::O);
        printUserInfo();

        while (gameStatus == InProgress) {
            for(int i = 0; i<2; i++){
                if (gameStatus == InProgress){
                    board.updateBoard(players[i]->makeMove(board), players[i]->getPlayerSymbol());
                    cout << board << endl;
                    gameStatus = checkGameStatus();
                    if (gameStatus == Win){
                        cout << "Player " << players[i]->convertPlayerSymbolToChar() << " has won the game." << endl;
                        break;
                    }
                    else if (gameStatus == Tie){
                        cout << "Tie" << endl;
                        break;
                    }
                }
            }
        }
    }
};

int main()
{
    int choose;
    Game* g;

    srand (time(NULL));

    do{
    g = new Game();
    g->startGame();
    cout << "Game is over. Choose what to do next (0=end 1=Start new game): " ;
    cin >> choose;
    } while(choose);
    return 0;
}
