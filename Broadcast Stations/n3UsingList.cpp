#include <iostream>
#include <map>

using namespace std;

class EdgeNode
{
public:
  static int countOfCreation;

  int from = -1, to = -1;
  EdgeNode * prev = NULL, * next = NULL;

  EdgeNode(int from, int to)
  {
    this->from = from;
    this->to = to;

    countOfCreation ++;
  }

  // ~EdgeNode()
  // {
  //   cout << "~EdgeNode" << endl;
  // }
};

class EdgeList
{
public:
  ~EdgeList()
  {
    // this->deleteAllNodes();
  }

  EdgeNode * getHead()
  {
    return this->head;
  }

  void addNode(EdgeNode * newNode)
  {
    if (this->head != NULL)
    {
      this->head->prev = newNode;
    }

    newNode->next = this->head;
    this->head = newNode;
  }

  void removeNode(EdgeNode * nodeToRemove)
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

  void deleteAllNodes()
  {
    EdgeNode * node = this->head;

    while (node != NULL)
    {
      EdgeNode * nextNode = node->next;

      delete node;

      node = nextNode;
    }
  }

  void printNodes()
  {
    EdgeNode * node = this->head;

    while (node != NULL)
    {
      cout << '(' << node->from << ',' << node->to << ") ";

      node = node->next;
    }

    cout << endl;
  }

private:
  EdgeNode * head = NULL;
};

int countOfVertices = -1;
EdgeList edgeList;
int countOfisVerticeCovered, minSumOfPowers = 0;

bool* isVerticeCovered;

short int * countOfEdgesFromVertice = NULL;

void input()
{
  cin >> countOfVertices;

  for (int i=1; i<=countOfVertices-1; i++)
  {
    int vertice1 = -1, vertice2 = -1;

    cin >> vertice1 >> vertice2;

    edgeList.addNode(new EdgeNode(vertice1, vertice2));
    edgeList.addNode(new EdgeNode(vertice2, vertice1));
  }

  isVerticeCovered = new bool[countOfVertices+1];

  for (int i=1; i<countOfVertices+1; i++)
  {
    isVerticeCovered[i] = false;
  }

  countOfEdgesFromVertice = new short int[countOfVertices+1];
}

void deallocate()
{
  delete [] isVerticeCovered;
  delete [] countOfEdgesFromVertice;
}

// count edges to uncovered vertice
int getVerticeWhichHasMaxEdge()
{
  int verticeWhichHasMaxEdge = 1;

  for (int i=1; i<=countOfVertices; i++)
  {
    countOfEdgesFromVertice[i] = 0;
  }

  EdgeNode * edgeCursor = edgeList.getHead();

  while (edgeCursor != NULL)
  {
    if (!isVerticeCovered[edgeCursor->to])
    {
      countOfEdgesFromVertice[edgeCursor->from] ++;
    }

    edgeCursor = edgeCursor->next;
  }

  for (int i=1; i<=countOfVertices; i++)
  {
    if (countOfEdgesFromVertice[i] > countOfEdgesFromVertice[verticeWhichHasMaxEdge])
    {
      verticeWhichHasMaxEdge = i;
    }
  }

  return verticeWhichHasMaxEdge;
}

void addPower(int station)
{
  minSumOfPowers ++;

  if (!isVerticeCovered[station])
  {
    isVerticeCovered[station] = true;
    countOfisVerticeCovered ++;
  }

  EdgeNode * edgeCursor1 = edgeList.getHead();

  // cover vertices near by station
  // and update edges
  while (edgeCursor1 != NULL)
  {
    if (edgeCursor1->from != station)
    {
      edgeCursor1 = edgeCursor1->next;
      continue;
    }

    EdgeNode * nextEdge = edgeCursor1->next;

    int verticeNearStation = edgeCursor1->to;

    // cover vertices near by station
    if (!isVerticeCovered[verticeNearStation])
    {
      isVerticeCovered[verticeNearStation] = true;
      countOfisVerticeCovered ++;
    }

    // update edges
    edgeList.removeNode(edgeCursor1);

    EdgeNode * edgeCursor2 = edgeList.getHead();

    while(edgeCursor2 != NULL)
    {
      if (edgeCursor2->from == verticeNearStation && edgeCursor2->to != station)
      {
        edgeList.addNode(new EdgeNode(station, edgeCursor2->to));
      }

      edgeCursor2 = edgeCursor2->next;
    }

    edgeCursor1 = nextEdge;
  }
}

int EdgeNode::countOfCreation = 0;

int main()
{
  input();

  edgeList.printNodes();

  while (countOfisVerticeCovered < countOfVertices)
  {
    int verticeWhichHasMaxEdge = getVerticeWhichHasMaxEdge();

    addPower(verticeWhichHasMaxEdge);

    edgeList.printNodes();
  }

  cout << minSumOfPowers << endl;

  edgeList.deleteAllNodes();
  deallocate();

  // cout << "count of creation of EdgeNode: " << EdgeNode::countOfCreation << endl;

  return 0;
}
