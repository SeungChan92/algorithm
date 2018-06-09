#include <iostream>
#include <string>

using namespace std;

int const MY_INT_MAX = 2000000000;

class Team
{
public:
	Team(int diff, int countOfBalloons);

	int getDiff()
	{
		return this->diff;
	}

	int getCountOfBalloons()
	{
		return this->countOfBalloons;
	}

	void reverseDiff()
	{
		this->diff = -1 * this->diff;
	}

private:
	int diff, countOfBalloons;
};

Team::Team(int diff, int countOfBalloons)
{
	this->diff = diff;
	this->countOfBalloons = countOfBalloons;
}

class PriorityQueueNode
{
public:
	Team * team;
	PriorityQueueNode* prev = NULL;
	PriorityQueueNode* next = NULL;

	PriorityQueueNode(Team* team);
};

PriorityQueueNode::PriorityQueueNode(Team* team)
{
	this->team = team;
}

class PriorityQueue
{
public:
	PriorityQueue()
	{
		Team* team = new Team(MY_INT_MAX, 0);
		this->head = new PriorityQueueNode(team);
		this->tail = this->head;
	}

	void add(Team* team);
	Team* pop();

	string getTeamList()
	{
		string teamList;
		PriorityQueueNode* cursor = head->next;

		while (cursor != NULL)
		{
			teamList += "(" + to_string(cursor->team->getDiff()) + ", " + to_string(cursor->team->getCountOfBalloons()) + ") ";

			cursor = cursor->next;
		}

		return teamList;
	}

private:
	PriorityQueueNode * head, * tail;
};

void PriorityQueue::add(Team* team)
{
	PriorityQueueNode* newNode = new PriorityQueueNode(team);

	this->tail->next = newNode;
	newNode->prev = this->tail;
	this->tail = newNode;
}

Team* PriorityQueue::pop()
{
	PriorityQueueNode* cursor = head;
	PriorityQueueNode* minDiffTeamNode = head;

	while (cursor->next != NULL)
	{
		cursor = cursor->next;

		if (cursor->team->getDiff() < minDiffTeamNode->team->getDiff())
		{
			minDiffTeamNode = cursor;
		}
	}

	// remove popedNode from the queue
	if (minDiffTeamNode == this->head)
	{
		this->head = this->head->next;
		this->head->prev = NULL;
	}
	else if (minDiffTeamNode == this->tail)
	{
		this->tail = this->tail->prev;
		this->tail->next = NULL;
	}
	else
	{
		minDiffTeamNode->prev->next = minDiffTeamNode->next;
		minDiffTeamNode->next->prev = minDiffTeamNode->prev;
	}

	return minDiffTeamNode->team;
}

class Storage
{
public:
	Storage(int maxBalloons);
	bool isOver();
	void add(Team* team);
	Team* pop();

	string getTeamList()
	{
		return this->teamQueue->getTeamList();
	}

	string getCountOfUsedBalloon()
	{
		return "(" + to_string(this->usedBalloons) + " / " + to_string(this->maxBalloons) + ")";
	}

private:
	int maxBalloons;
	int usedBalloons = 0;
	PriorityQueue* teamQueue;
};

Storage::Storage(int maxBalloons)
{
	this->maxBalloons = maxBalloons;
	this->teamQueue = new PriorityQueue();
}

bool Storage::isOver()
{
	if (this->usedBalloons > this->maxBalloons)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Storage::add(Team* team)
{
	this->teamQueue->add(team);
	this->usedBalloons += team->getCountOfBalloons();
}

Team* Storage::pop()
{
	// Maybe storage capability is over now.

	Team * teamToPop, * popedTeam;
	int countOfOverBalloons = this->usedBalloons - this->maxBalloons;

	popedTeam = this->teamQueue->pop();
	this->usedBalloons -= popedTeam->getCountOfBalloons();

	if (popedTeam->getCountOfBalloons() <= countOfOverBalloons)
	{
		teamToPop = popedTeam;
	}
	else
	{
		Team* teamToAddAgain = new Team(popedTeam->getDiff()
			, popedTeam->getCountOfBalloons() - countOfOverBalloons);
		this->add(teamToAddAgain);
		teamToPop = new Team(popedTeam->getDiff(), countOfOverBalloons);
	}

	return teamToPop;
}

int main()
{
	int totalDistance = 0;
	int countOfTeams, countOfBalloonsInA, countOfBalloonsInB;

	cin >> countOfTeams >> countOfBalloonsInA >> countOfBalloonsInB;

	Storage storageA(countOfBalloonsInA);
	Storage storageB(countOfBalloonsInB);

	for (int i = 0; i<countOfTeams; i++)
	{
		// diff: distanceFromA - distanceFromB
		int countOfBalloonsForTeam, distanceFromA, distanceFromB, diff;

		cin >> countOfBalloonsForTeam >> distanceFromA >> distanceFromB;

		bool closerToA = (distanceFromA - distanceFromB) <= 0;

		if (closerToA)
		{
			diff = distanceFromB - distanceFromA;
			Team* team = new Team(diff, countOfBalloonsForTeam);

			storageA.add(team);
			totalDistance += distanceFromA * countOfBalloonsForTeam;

			while (storageA.isOver())
			{
				Team* teamToMove = storageA.pop();
				storageB.add(teamToMove);

				totalDistance += teamToMove->getDiff() * teamToMove->getCountOfBalloons();

				teamToMove->reverseDiff();
			}
		}
		else
		{
			diff = distanceFromA - distanceFromB;
			Team* team = new Team(diff, countOfBalloonsForTeam);

			storageB.add(team);
			totalDistance += distanceFromB * countOfBalloonsForTeam;

			while (storageB.isOver())
			{
				Team* teamToMove = storageB.pop();
				storageA.add(teamToMove);

				totalDistance += teamToMove->getDiff() * teamToMove->getCountOfBalloons();

				teamToMove->reverseDiff();
			}
		}

		cout << "StorageA: " << storageA.getTeamList() << endl;
		cout << "StorageB: " << storageB.getTeamList() << endl;
		cout << "used of A: " << storageA.getCountOfUsedBalloon() << endl;
		cout << "used of B: " << storageB.getCountOfUsedBalloon() << endl;
		cout << "totalDistance: " << totalDistance << endl << endl;
	}

	cout << totalDistance << endl;

	return 0;
}
