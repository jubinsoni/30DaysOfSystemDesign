# include <iostream>
# include <vector>

using namespace std;

// Requirement : 
// Book a room for the meeting and return the name of the room booked and history of the meetings booked
// Write an Api which Accepts start time, end time and returns meeting room name

class Meeting; // this is forward declaration...this to tell compiler while creating vector of Meeting class 
typedef vector<Meeting> Calendar;

class Room
{
private:
	// properties
	string name;
	Calendar calendar;
public:

	//Constructor
	Room(string);

	//getters and setters
	string getName();

	//functionality
	bool book(int,int);
};

class Meeting
{
private:
	//properties
	int start;
	int end;
	Room room;
public:
	//Constructor
	Meeting(int ,int,Room);

	//getters and setters
	int getStart();
	int getEnd();
};

class Scheduler
{
	vector<Room> rooms;
public:
	//Constructor
	Scheduler(vector<Room>);
	string book(int,int);
};

Room::Room(string name)
{
	this->name = name;
}

string Room::getName()
{
	return name;
}

bool Room::book(int start, int end)
{
	for(Meeting m : calendar)
	{
		if(m.getStart() < end && start < m.getEnd())
		{
			return false;
		}
	}

	Meeting meeting(start,end,*this);
	calendar.push_back(meeting);

	return true;
}

// We have done a member initialization for the room variable
Meeting::Meeting(int start,int end,Room room): room(room)
{
	this->start = start;
	this->end = end;
}

int Meeting::getStart()
{
	return start;
}

int Meeting::getEnd()
{
	return end;
}


Scheduler::Scheduler(vector<Room> rooms)
{
	this->rooms = rooms;
}

string Scheduler::book(int start,int end)
{
	for(Room &room: rooms)
	{
		bool flag = room.book(start,end);
		if(flag == true)
		{
			return room.getName();
		}
	}

	return "No rooms available";
}


int main()
{
	Room room1("Atlas");
	Room room2("Nexus");
	Room room3("HolyCow");

	vector<Room> roomVec;
	roomVec.push_back(room1);
	roomVec.push_back(room2);
	roomVec.push_back(room3);

	Scheduler scheduler(roomVec);

	cout << scheduler.book(2,5) << "\n";	//Atlas
	cout << scheduler.book(5,8) << "\n";	//Atlas
	cout << scheduler.book(4,8) << "\n";	//Nexus
	cout << scheduler.book(3,6) << "\n";	//Holycow
	cout << scheduler.book(7,8) << "\n";	//Holycow
	cout << scheduler.book(6,9) << "\n";	//Atlas
	return 0;
}