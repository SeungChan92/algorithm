#include <iostream>

using namespace std;

class EdgeNode
{
public:
  int from = -1, to = -1;
  EdgeNode * prev = NULL, * next = NULL;
}

class EdgeList
{
public:
  getHead()
  {
    return this->head;
  }

  addNode(EdgeNode * newNode)
  {
    if (this->head != NULL)
    {
      this->head->prev = newNode;
    }

    newNode->next = this->head;
    this->head = newNode;
  }

  removeNode(EdgeNode * nodeToRemove)
  {
    if (nodeToRemove == head)
    {
      head = head->next;
    }
    else
    {
      nodeToRemove->prev->next = nodeToRemove->next;
    }

    if (nodeToRemove->next != NULL)
    {
      nodeToRemove->next->prev = nodeToRemove->prev;
    }

    delete(nodeToRemove);
  }

private:
  EdgeNode * head = NULL;
}

int countOfVertices = -1;
int * edgeFrom = NULL, * edgeTo = NULL;
int countOfisVerticeCovered, minSumOfPowers = 0;

bool* isVerticeCombined;

void input()
{
  cin >> countOfVertices;

  edgeFrom = new int[countOfVertices];
  edgeTo = new int[countOfVertices];

  for (int i=1; i<=countOfVertices-1; i++)
  {
    cin >> edgeFrom[i] >> edgeTo[i];
  }

  isVerticeCombined = new bool[countOfVertices+1];

  for (int i=1; i<countOfVertices+1; i++)
  {
    isVerticeCombined[i] = false;
  }
}

void addPower(int station)
{
  // cover vertices connected with the station
  for (int i=1; i<=countOfVertices; i++)
  {
    if (isVerticeCovered[i]) continue;


  }
}

int main()
{
  input();

  while (countOfisVerticeCovered < countOfVertices)
  {
    int verticeWhichHasMaxEdge = getVerticeWhichHasMaxEdge();

    addPower(verticeWhichHasMaxEdge);
  }

  cout << minSumOfPowers << endl;

  return 0;
}
