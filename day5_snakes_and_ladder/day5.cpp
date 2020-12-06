# include <iostream>
# include <vector>
# include <unordered_map>

using namespace std;

// constructor is used to initialize default values when nothing is sent as argument
// constructor is used to initialize setter value when arguemnt is passed

class Snake
{

private:
	// properties
	int start;
	int end;
public:
	// constructor
	Snake(int start,int end);

	// getters and setters
	int getStart();
	int getEnd();
};

class Ladder
{

private:
	// properties
	int start;
	int end;
public:
	// constructor
	Ladder(int start,int end);

	// getters and setters
	int getStart();
	int getEnd();
};

Snake::Snake(int start,int end)
{
	this->start = start;
	this->end = end;
}

int Snake::getStart()
{
	return start;
}

int Snake::getEnd()
{
	return end;
}

Ladder::Ladder(int start,int end)
{
	this->start = start;
	this->end = end;
}

int Ladder::getStart()
{
	return start;
}

int Ladder::getEnd()
{
	return end;
}

class Player
{
private:
	int id;
	string name;
	int currentPosition;

public:

	//constructor
	Player(string name);

	//getters and setters
	int getId();
	string getName();
	int getCurrentPosition();
	void setCurrentPosition(int currentPosition);

	// functionality
	int getUniqueId();
};

Player::Player(string name)
{
	this->name = name;
	this->id = getUniqueId();
	this->currentPosition = 0;

}

int Player::getId()
{
	return id;
}

string Player::getName()
{
	return name;
}

int Player::getCurrentPosition()
{
	return currentPosition;
}

void Player::setCurrentPosition(int currentPosition)
{
	this->currentPosition = currentPosition;
}

int Player::getUniqueId()
{
	static int playerId = 1;
	playerId = playerId + 1;
	return playerId;
}

class Game
{
private:
	vector<Player> players;
	int currentTurn;
	Player* winner;
	unordered_map<int,int> snakesAndLadders;
public:
	Game(vector<Snake>& snakes,vector<Ladder>& ladders,vector<Player>& players);
	vector<Player> getPlayers();
	Player* getWinner();
	bool roll(Player player,int diceValue);
	void nextPlayer();
};

vector<Player> Game::getPlayers() {
	return players;
}

Player* Game::getWinner() {
	return winner;
}

Game::Game(vector<Snake>& snakes,vector<Ladder>& ladders,vector<Player>& players)
{
	this->players = players;

	for(Snake snake : snakes)
	{
		snakesAndLadders[snake.getStart()] = snake.getEnd();
	}

	for(Ladder ladder : ladders)
	{
		snakesAndLadders[ladder.getStart()] = ladder.getEnd();	
	}

	this->currentTurn = 0;
	this->winner = nullptr;
}

bool Game::roll(Player player, int diceValue)
{
	if(winner != nullptr || diceValue > 6 || diceValue < 1 || players.at(currentTurn).getId())
	{
		return false;
	}

	int destination = players.at(currentTurn).getCurrentPosition() + diceValue;
	if(destination <= 100)
	{
		if(snakesAndLadders.find(destination) != snakesAndLadders.end())
		{
			players.at(currentTurn).setCurrentPosition(snakesAndLadders[destination]);
		}
		else
		{
			players.at(currentTurn).setCurrentPosition(destination);	
		}
	}

	if(destination == 100)
	{
		winner = &(players.at(currentTurn));
	}

	nextPlayer();

	return true;
}

void Game::nextPlayer()
{
	currentTurn = (currentTurn + 1)%players.size();
}

int main()
{
	Player p1("Robert");
	Player p2("Stannis");
	Player p3("Renly");

	Snake s1(17, 7);
	Snake s2(54, 34);
	Snake s3(62, 19);
	Snake s4(64, 60);
	Snake s5(87, 36);
	Snake s6(92, 73);
	Snake s7(95, 75);
	Snake s8(98, 79);

	Ladder l1(1, 38);
	Ladder l2(4, 14);
	Ladder l3(9, 31);
	Ladder l4(21, 42);
	Ladder l5(28, 84);
	Ladder l6(51, 67);
	Ladder l7(72, 91);
	Ladder l8(80, 99);

	vector<Snake> s = {s1, s2, s3, s4, s5, s6, s7, s8};
	vector<Ladder> l = {l1, l2, l3, l4, l5, l6, l7, l8};
	vector<Player> p = {p1, p2, p3};

	Game game(s,l,p);

//	for(auto const& pair: game.getSnakesAndLadders())
//	{
//		cout << pair.first << " " << pair.second << "\n";
//	}

	while(game.getWinner() == nullptr)
	{
		int diceVal = (rand()%6)+1;
		game.roll(p1, diceVal);
		diceVal = (rand()%6)+1;
		game.roll(p2, diceVal);
		diceVal = (rand()%6)+1;
		game.roll(p3, diceVal);
	}

	cout << "The winner is: " << game.getWinner()->getName() << "\n";

	cout << "All Scores: ";
	for(Player p: game.getPlayers())
		cout << p.getCurrentPosition() << " ";
	return 0;
}