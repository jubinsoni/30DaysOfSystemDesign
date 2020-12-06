// Requirement : 
// Design a Task Planner like JIRA

// Inputs : 
// Program should take as input 2 or more drivers and a set of riders requesting rides

// Finctionalities expected : 
// 1) User should be able to Create Task of Type Story,Feature and Bug
// 2) Every Task should be having status
// 3) Stories can have further subtracts
// 4) Should be able to change status of any task
// 5) User should be able to create any sprint
// 6) Should be able to add any task to sprint and remove it
// 7) Should be able to print (a) Delayed task(s) (b) Sprint details (c) Tasks assigned to the user

# include <iostream>
# include <vector>

using namespace std;

// forward declaration of class
// To let compiler know that class blueprint is down below
class Task;

enum TaskType {STORY,FEATURE,BUG};
enum TaskStatus {OPEN,IN_PROGRESS,RESOLVED,DELAYED,COMPLETED};

class Sprint
{
private:
	// properties
	int begin;
	int end;
	string name;
	vector<Task> tasks;
public:

	//Constructor
	Sprint(int begin,int end,string name);

	//getters and setters
	vector<Task> getTasks();

	//functionalites
	void addTask(Task& task);
	void printDetails();
	void eraseTask(int taskNumber);

	// operator overloading
	bool operator==(Sprint sprint);
};

Sprint::Sprint(int begin,int end,string name)
{
	this->begin = begin;
	this->end = end;
	this->name = name;
}

vector<Task> Sprint::getTasks()
{
	return tasks;
}

void Sprint::addTask(Task& task)
{
	tasks.push_back(task);
}

void Sprint::printDetails()
{
	cout << "-----sprint details------" << endl;
	cout << "sprint name : " << this->name << endl;
	cout << "sprint begin : " << this->begin << endl;
	cout << "sprint end : " << this->end << endl;
	cout << "-----------" << endl;
}

void Sprint::eraseTask(int taskNumber)
{
	tasks.erase(tasks.begin() + taskNumber);
}

inline bool Sprint::operator==(Sprint sprint)
{
	return (this->begin == sprint.begin) && (this->end == sprint.end) && (this->name == sprint.name) ;
}

class User
{
private:
	vector<Task> taskList;
	vector<Sprint> sprintList;
public:
	Task createTask(TaskType taskType);
	Task createTask(string name);
	Sprint createSprint(int begin,int end,string name);
	bool addToSprint(Sprint& sprint,Task& task);
	bool removeFromSprint(Sprint& sprint,Task& task);
	bool changeStatus(Task& task,TaskStatus taskStatus);
	void printAllTasks();
};

class Task
{
private:
	//properties
	int id;
	string subtract;
	User user;
	TaskType taskType;
	TaskStatus taskStatus;
public:
	//Constructor
	Task();
	//getters and setters
	int getId();
	void setSubtract(string subtract);
	void setUser(User user);
	void setTasktype(TaskType taskType);
	void setTaskStatus(TaskStatus taskStatus);
	int getUniqueId();
};

Task::Task()
{
	this->id = getUniqueId();
	this->taskStatus = TaskStatus::OPEN;
}

int Task::getId()
{
	return id;
}

void Task::setSubtract(string subtract)
{
	this->subtract = subtract;
}

void Task::setUser(User user)
{
	this->user = user;
}

void Task::setTasktype(TaskType taskType)
{
	this->taskType = taskType;
}

void Task::setTaskStatus(TaskStatus taskStatus)
{
	this->taskStatus = taskStatus;
}

int Task::getUniqueId()
{
	static int taskId = 1;
	taskId = taskId + 1;
	return taskId;
}

Task User::createTask(TaskType taskType)
{
	if(taskType == TaskType::STORY)
	{
		cout << "Warning! Task of type story is being created with no subtract" << endl;	
	}

	Task task;
	task.setTasktype(taskType);
	task.setUser(*this);
	taskList.push_back(task);

	return task;
}

Task User::createTask(string subtract)
{
	Task task;
	task.setTasktype(TaskType::STORY);
	task.setSubtract(subtract);
	task.setUser(*this);
	taskList.push_back(task);

	return task;
}

Sprint User::createSprint(int begin, int end,string name)
{
	Sprint sprint(begin,end,name);
	sprintList.push_back(sprint);

	return sprint;
}

bool User::addToSprint(Sprint &sprint, Task &task)
{
	for(Sprint spr : sprintList)
	{
		if(spr == sprint)
		{
			sprint.addTask(task);
			return true;
		}
	}
	return false;
}

bool User::removeFromSprint(Sprint &sprint, Task &task)
{
	vector<Task> taskList;
	for(Sprint spr : sprintList)
	{
		if(spr == sprint)
		{
			taskList = sprint.getTasks();
			break;
		}
	}

	int i = 0;

	for(Task t : taskList)
	{
		if(t.getId() == task.getId())
		{
			sprint.eraseTask(i);
			return true;
		}
		i = i + 1;
	}
	return false;
}

void User::printAllTasks()
{
	for(Task task : taskList)
	{
		cout << task.getId() << " ";
	}
	cout << endl;
}

bool User::changeStatus(Task &task, TaskStatus taskStatus)
{
	for(Task &t : taskList)
	{
		 if(t.getId() == task.getId())
		{
			t.setTaskStatus(taskStatus);
			return true;
		}
	}
	return false;
}

int main()
{
	User user1, user2;
	Task task1 = user1.createTask(TaskType::FEATURE);
	Task task11 = user1.createTask(TaskType::BUG);
	Task task2 = user2.createTask(TaskType::BUG);
	Task task22 = user2.createTask("This is a subtract");

	Sprint sprint1 = user1.createSprint(22,33,"Sprint1");
	Sprint sprint2 = user2.createSprint(44,55,"Sprint2");

	cout << user1.changeStatus(task11, TaskStatus::IN_PROGRESS) <<endl ;//1

	cout << user1.addToSprint(sprint1, task1) << "\n"; //1
	cout << user1.addToSprint(sprint1, task11) << "\n"; //1
	cout << user1.addToSprint(sprint2, task1) << "\n"; //0
	cout << user1.removeFromSprint(sprint1, task11) << "\n"; //1
	cout << user2.addToSprint(sprint1, task1) << "\n"; //0
	cout << user2.removeFromSprint(sprint1, task2) << "\n"; //0
	cout << user2.addToSprint(sprint2, task1) << "\n"; //1
	cout << user2.addToSprint(sprint2, task2) << "\n"; //1

	sprint1.printDetails();
	cout << endl;
	user1.printAllTasks();
	user2.printAllTasks();
	
	return 0;
}