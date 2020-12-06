// Requirement : 
// Design a ride sharing application where drivers can offer rides(origin,destination,no.of seats),any rider can request rides(origin,destination,no of seats)

// Algo to implement : 
// 1. When the ride closes,show the amount charged to the rider
// 2. Ride amount (if No. of seats >= 2) : No of kilometers * No of seats * 0.75 * Amount charged per KM
// 3. Ride amount (if No. of seats = 1) : No of kilometers * Amount charged per KM

// Inputs : 
// Program should take as input 2 or more drivers and a set of riders requesting rides

// Assumptions : 
// 1. Amount charged per KM = 20
// 2. No of Kilometers = destination - origin
// 3. All values are integer

// Test Case : 
// INPUT : A requests 50,60,1
// OUTPUT : Ride Amount : 10*20(Amount/Km) = 200

// INPUT : A requests 50,60,2
// OUTPUT : Ride Amount : 10*2*0.75*20(Amount/Km) = 300

// Finctionalities expected : 
// 1. Add Driver(name)
// 2. Add Rider(name)
// 3. Create Ride(id,origin,destination,no of seats)
// 4. Create/Update(id,origin,destination,no of seats)
// 5. Withdraw Ride(id)
// 6. Close ride and return ride amount charged


# include <iostream>
# include <vector>

using namespace std;

enum RideStatus{IDLE,CREATED,WITHDRAWN,COMPLETED};

class Ride 
{
public:
	// constant
	static const int AMT_PER_KM = 20;

	// constructor
	Ride();

	//getters and setters declaration
	int getId();
	void setId(int id);

	void setOrigin(int origin);

	void setDest(int dest);

	void setSeats(int seats);

	RideStatus getRideStatus();
	void setRideStatus(RideStatus rideStatus);

	//functionality
	int calculateFare(bool);

private:
	//properties
	int id;
	int origin;
	int dest;
	int seats;
	RideStatus rideStatus;
};

Ride::Ride()
{
	id = 0;
	origin = 0;
	dest = 0;
	seats = 0;
	rideStatus = RideStatus::IDLE;
}

int Ride::getId() 
{
	return id;
}

void Ride::setId(int id)
{
	this->id = id;
}

void Ride::setOrigin(int origin)
{
	this->origin = origin;
}

void Ride::setDest(int dest)
{
	this->dest = dest;
}

void Ride::setSeats(int seats)
{
	this->seats = seats;
}

RideStatus Ride::getRideStatus()
{
	return rideStatus;
}

void Ride::setRideStatus(RideStatus rideStatus)
{
	this->rideStatus = rideStatus;
}

int Ride::calculateFare(bool isPriorityRider)
{
	int dist = dest - origin;
	if(seats <= 1)
	{
		if(isPriorityRider == true)
		{
			return dist * AMT_PER_KM * 0.75;
		}

		return dist * AMT_PER_KM * 1;
	}
	else
	{
		if(isPriorityRider == true)
		{
			return dist * seats * AMT_PER_KM * 0.5;
		}

		return dist * seats * AMT_PER_KM * 0.75;
	}
}

class Person
{
public:
	string name;
};

class Driver: private Person
{
public:
	// constructor
	Driver(string);
};

Driver::Driver(string name)
{
	this->name = name;
}

class Rider: private Person
{
public:
	// constructor
	Rider(string);

	//functionality
	void createRide(int,int,int,int);
	void updateRide(int,int,int,int);
	void withdrawRide(int);
	int closeRide();

private:
	vector<Ride> completedRides;
	Ride currentRide;
};

Rider::Rider(string name)
{
	this->name = name;
}

void Rider::createRide(int id,int origin,int dest,int seats)
{
	if(origin >= dest)
	{
		cout << "wrong value of origin and dest provided " << endl;
		return;
	}

	currentRide.setId(id);
	currentRide.setOrigin(origin);
	currentRide.setDest(dest);
	currentRide.setSeats(seats);
	currentRide.setRideStatus(RideStatus::CREATED);
}

void Rider::updateRide(int id,int origin,int dest,int seats)
{
	if(currentRide.getRideStatus() == RideStatus::WITHDRAWN)
	{
		cout << "can't update as ride was withdrawn " << endl;
		return;
	}

	if(currentRide.getRideStatus() == RideStatus::COMPLETED)
	{
		cout << "can't update as ride was completed " << endl;
		return;
	}

	createRide(id,origin,dest,seats);
}

void Rider::withdrawRide(int id)
{
	if(currentRide.getId() != id)
	{
		cout << "Wrong ride Id.Ride already complete"<< endl;
		return;
	}

	if(currentRide.getRideStatus() != RideStatus::CREATED)
	{
		cout << "Ride wasn't in progress.Can't withdraw ride"<< endl;
		return;
	}

	currentRide.setRideStatus(RideStatus::WITHDRAWN);
}

int Rider::closeRide()
{
	if(currentRide.getRideStatus() != RideStatus::CREATED)
	{
		cout << "Ride wasn't in progress.Can't close ride" << endl;
		return 0;
	}

	currentRide.setRideStatus(RideStatus::COMPLETED);
	completedRides.push_back(currentRide);

	bool isPriorityRider = completedRides.size() >= 10;

	return currentRide.calculateFare(isPriorityRider);

}

int main()
{
	Rider rider("Yamraj");
	Driver driver("Chitragupta");

	rider.createRide(1, 50, 60, 1);
	cout << rider.closeRide() << endl;
	rider.updateRide(1, 50, 60, 2);
	cout << rider.closeRide() << endl;

	cout << "-------" << endl;

	rider.createRide(1, 50, 60, 1);
	rider.withdrawRide(1);
	rider.updateRide(1, 50, 60, 2);
	cout << rider.closeRide() << endl;

	cout << "-------" << endl;

	rider.createRide(1, 50, 60, 1);
	rider.updateRide(1, 50, 60, 2);
	cout << rider.closeRide() << endl;

	return 0;
}