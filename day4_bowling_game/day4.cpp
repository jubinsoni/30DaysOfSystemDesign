# include <iostream>
# include <vector>
# include <unordered_map>
# include <cstring>

using namespace std;

class Player
{

public:
	// Declare constants
	static const int MAX_ROLLS_ALLOWED = 23;

	//Constructor
	Player(string name);

	//getters and setters
	string getName();
	int getScore();

	//functionality
	bool isStrike();
	bool isSpare();
	void roll(int pins);
	bool isCanPlay();
	void updateScore();

private:
	//properties
	string name;
	int score;
	int rolls[MAX_ROLLS_ALLOWED];
	bool firstRoll;
	int frameIndex;
	bool canPlay;
	int currentRoll;
};

Player::Player(string name)
{
	memset(rolls,0,sizeof(rolls));
	this->name = name;
	this->score = 0;
	this->firstRoll = true;
	this->frameIndex = 0;
	this->canPlay = true;
	this->currentRoll = 0;
}

bool Player::isStrike()
{
	bool result = (this->firstRoll == true) && (rolls[frameIndex] == 10);
	return result;
}

bool Player::isSpare()
{
	bool result = rolls[frameIndex] + rolls[frameIndex + 1] == 10;
	return result;
}

bool Player::isCanPlay() {
	return canPlay;
}

void Player::updateScore()
{
	if(isStrike() == true)
	{
		score = score + 20;
		currentRoll = currentRoll + 1;
		rolls[currentRoll] = 0;
		frameIndex = frameIndex + 2;
		if(frameIndex >= MAX_ROLLS_ALLOWED)
		{
			this->canPlay = false;
		}
	}
	else
	{
		if(frameIndex >= MAX_ROLLS_ALLOWED - 1)
		{
			score = score + rolls[frameIndex];
			this->canPlay = false;
		}
		else if(firstRoll == true)
		{
			firstRoll = false;
		}
		else
		{
			 if(isSpare())
			 {
			 	score = score + 5;
			 }

			 score = score + rolls[frameIndex] + rolls[frameIndex + 1];
			 frameIndex = frameIndex + 2;
			 firstRoll = true;
			 if(frameIndex >= MAX_ROLLS_ALLOWED - 3)
			 {
			 	this->canPlay = false;
			 }
		}
	}
}

void Player::roll(int pins)
{
	if(this->canPlay == false)
	{
		return;
	}
	currentRoll = currentRoll + 1;
	rolls[currentRoll] = pins;
	updateScore();
}

string Player::getName()
{
	return name;
}

int Player::getScore()
{
	return score;
}

class GameSession
{
private:
	// properties
	int alley;
	int id;
	vector<Player> players;
public:
	//constructor
	GameSession();

	//getters and setters
	void setAlley(int alley);
	int getId();
	void setPlayers(vector<Player> players);

	//functionality
	int getUniqueId();
	bool declareWinner();
	void makeRoll(Player &player,int pins);
};

class Game
{
private:
	//properties
	unordered_map<int,GameSession> gameSessions;
public:
	//functionalities
	static vector<int> alleys;
	static void makeActive(int alley);
	int createSession(vector<Player>& players);
	void roll(int index, Player player, int pins);
	void declareWinner(int index);
};


bool GameSession::declareWinner()
{
	int maxScore = 0;
	Player *winner = nullptr;
	for(Player &p : players)
	{
		if(p.isCanPlay() == true)
		{
			cout << "Player " << p.getName().c_str() << "hasn't completed yet. The current score: " << p.getScore() << endl;
			cout << "Match in progress" << endl;
			return false;
		}

		if(p.getScore() > maxScore)
		{
			maxScore = p.getScore();
			winner = &p;
		}
	}
	if(winner != nullptr)
	{
		cout << "The winner is : " << winner->getName().c_str() << " with a score of " << winner->getScore() << endl;
	}

	Game::makeActive(this->alley);

	return true;
}

GameSession::GameSession()
{
	this->alley = -1;
	this->id = getUniqueId();
	this->players.clear();
}

int GameSession::getUniqueId()
{
	static int gameSessionId = 1;
	gameSessionId = gameSessionId + 1;
	return gameSessionId;
}

void GameSession::setAlley(int alley)
{
	this->alley = alley;
}

int GameSession::getId()
{
	return id;
}

void GameSession::setPlayers(vector<Player> players)
{
	this->players = players;
}

void GameSession::makeRoll(Player &player,int pins)
{
	for(Player &p : players)
	{
		if(p.getName() == player.getName())
		{
			p.roll(pins);
		}
	}
}

vector<int> Game::alleys = {1,2,3,4};

int Game::createSession(vector<Player> &players)
{
	if(Game::alleys.size() == 0)
	{
		cout << "All alleys are currently occupied!!" << endl;
		return 0;
	}

	GameSession gameSession;
	gameSession.setPlayers(players);
	gameSession.setAlley(Game::alleys.back());
	Game::alleys.pop_back();
	gameSessions[gameSession.getId()] = gameSession;

	return gameSession.getId();
}

void Game::makeActive(int alley)
{
	Game::alleys.push_back(alley);
}

void Game::declareWinner(int index)
{
	bool winnerFlag = gameSessions[index].declareWinner();

	if(winnerFlag == false)
	{
		cout << "No winner for this game yet !! " << endl;
	}
}

void Game::roll(int index, Player player, int pins)
{
	GameSession *gameSession = &gameSessions[index];
	gameSession->makeRoll(player,pins);
}

int main()
{
	Player p1("Thor");
    Player p2("Loki");
    Player p3("Hela");
    Player p4("Odin");

    vector<Player> vec;
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    vec.push_back(p4);

    Game g;
    int index = g.createSession(vec);

    vector<int> s1;
    vector<int> s2;
    vector<int> s3;
    vector<int> s4;
    int score;
    for(int i=0; i<20; ++i)
    {
    	score = abs(rand()%10);
    	s1.push_back(score);
        g.roll(index, p1, score);
    	score = abs(rand()%10);
    	s2.push_back(score);
        g.roll(index, p2, score);
    	score = abs(rand()%10);
    	s3.push_back(score);
        g.roll(index, p3, score);
    	score = abs(rand()%10);
    	s4.push_back(score);
        g.roll(index, p4, score);
    }
    cout << "Player 1: ";
    for(int i: s1)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 2: ";
    for(int i: s2)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 3: ";
    for(int i: s3)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 4: ";
    for(int i: s4)
    	cout << i << " ";
    cout << "\n";


    g.createSession(vec);
    g.createSession(vec);
    g.createSession(vec);
    g.declareWinner(index);
    g.createSession(vec);
    
	return 0;
}