#include <iostream>
#include <string>
#include <array>

using namespace std;

const string playerSelectMsg = "Please select player type (0=Human, 1=SmartAI, 2=RandomAI):";

enum CellType {EMPTY=' ', O='O', X='X'};
enum PlayerType {Human, SmartAI, RandomAI};
enum GameStatus {InProgress, Win, Tie};

class Board{
    CellType _board[3][3];
public:
    Board(){
        for(int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j )
            {
                _board[i][j] = CellType::EMPTY;
            }
    }

    GameStatus checkStatus() {
        int sum;
        bool emptyExist = false;

        for(int i=0; i<3; i++){
            sum = 0;
            for(int j=0; j<3; j++){

                if (!emptyExist && _board[i][j] == EMPTY) {emptyExist = true;}

                sum += _board[i][j];
            }
            if (sum == X*3 || sum == O*3)
                return Win;
        }

        for(int j=0; j<3; j++){
            sum = 0;
            for(int i=0; i<3; i++){
                sum += _board[i][j];
            }
            if (sum == X*3 || sum == O*3)
                return Win;
        }

        sum = 0;
        for(int i=0; i < 2; i++)
            sum += _board[i][i];
        if (sum == X*3 || sum == O*3)
            return Win;

        sum = 0;
        for(int i=0, j=2; i<2; i++,j--)
            sum += _board[i][j];
        if (sum == X*3 || sum == O*3)
            return Win;

        if (emptyExist)
            return InProgress;
        else
            return Tie;
    }

    void updateBoard(int move,const CellType &p) {
        _board[move % 3][(int) move / 3] = p;
    }

    bool validMove(int& move) const {
        return _board[move % 3][(int) move / 3] == EMPTY ? true : false;
    }

    void printAvailableMoves() const {
        for(int j = 0; j < 3; ++j){
            std::cout << " "
               << (_board[0][j] == EMPTY ? static_cast<char>(0+3*j+48) : static_cast<char>(_board[0][j]) )
               << " | "
               << (_board[1][j] == EMPTY ? static_cast<char>(1+3*j+48) : static_cast<char>(_board[1][j]) )
               << " | "
               << (_board[2][j] == EMPTY ? static_cast<char>(2+3*j+48) : static_cast<char>(_board[2][j]) )
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
               << static_cast<char>(b._board[0][j])
               << " | "
               << static_cast<char>(b._board[1][j])
               << " | "
               << static_cast<char>(b._board[2][j])
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
    PlayerType _playerType;
    CellType _playerSymbol;
public:
    Player(PlayerType p, CellType s):_playerType{p}, _playerSymbol{s}{}
    virtual CellType& getPlayerSymbol() {return _playerSymbol;}
    virtual int makeMove(const Board&) { return 0; };
    friend ostream & operator<<(ostream &os, const Player& p) {
        switch(p._playerType)
            {
                case Human      : os << "Human";    break;
                case SmartAI    : os << "SmartAI";  break;
                case RandomAI   : os << "RandomAI"; break;
            }
        os << " plays with "
           << static_cast<char>(p._playerSymbol);
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
            cout << "Player " << static_cast<char>(_playerSymbol) << " Make a move (1-9):";
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
    int makeMove(const Board&) { throw; return 0; }
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
    std::array<Player*,2> _players;
    Board _board;
    GameStatus _gameStatus;

  public:
    Game(){
        int choose;

        cout << playerSelectMsg;
        cin >> choose;
        _players[0] = Player::Create(static_cast<PlayerType>(choose), CellType::X);

        cout << playerSelectMsg;
        cin >> choose;
        _players[1] = Player::Create(static_cast<PlayerType>(choose), CellType::O);

        printUserInfo();
    }
    ~Game(){
        // TODO implement destructor
    }

    void printUserInfo(){
        for(int i =0; i<2; i++)
        cout << *_players[i] << endl;
    }

    GameStatus checkGameStatus(){
        return _board.checkStatus();
    }

    void startGame(){
        while (_gameStatus == InProgress) {
            for(int i = 0; i<2; i++){
                if (_gameStatus == InProgress){
                    _board.updateBoard(_players[i]->makeMove(_board), _players[i]->getPlayerSymbol());
                    _gameStatus = checkGameStatus();
                    if (_gameStatus == Win){
                        cout << "Player " << static_cast<char>(_players[i]->getPlayerSymbol()) << " has won the game." << endl;}
                     else
                        cout << "Tie" << endl;
                }
            }
        }
    }
};

int main()
{
    int choose;
    do{
    Game g;
    g.startGame();
    cout << "Game is over. Choose what to do next (0=end 1=Start new game): " ;
    cin >> choose;
    } while(choose);
    return 0;
}
