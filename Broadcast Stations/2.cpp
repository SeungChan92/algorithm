#include <iostream>

using namespace std;

class AdjacencyNode
{
public:
  int adjacency;
  AdjacencyNode * next = NULL;

  AdjacencyNode() { }

  AdjacencyNode(int adjacency)
  {
    this->adjacency = adjacency;
  }
};

int countOfVertices, minSumOfPowers = 0;
// adjacencies[from] -> to1 -> to2 -> ...
AdjacencyNode * adjacencies;
int * effectOfVertices, * powerOfVertices;
bool * isVerticeCovered;

void input()
{
  cin >> countOfVertices;

  adjacencies = new AdjacencyNode[countOfVertices+1];
  effectOfVertices = new int[countOfVertices+1] { };
  powerOfVertices = new int[countOfVertices+1] { };
  isVerticeCovered = new bool[countOfVertices+1] { };

  // add effect for itself vertice
  for (int i=1; i<=countOfVertices; i++)
  {
    effectOfVertices[i] = 1;
  }

  // read adjacencies
  for (int i=1; i<=countOfVertices-1; i++)
  {
    int vertice1, vertice2;

    cin >> vertice1 >> vertice2;

    effectOfVertices[vertice1] ++;
    effectOfVertices[vertice2] ++;

    AdjacencyNode * cursor = &adjacencies[vertice1];
    while (cursor->next != NULL)
    {
      cursor = cursor->next;
    }
    cursor->next = new AdjacencyNode(vertice2);

    cursor = &adjacencies[vertice2];
    while (cursor->next != NULL)
    {
      cursor = cursor->next;
    }
    cursor->next = new AdjacencyNode(vertice1);
  }
}

int pickMaxEffectVertice()
{
  int maxEffectVertice = 1;

  for (int i=2; i<=countOfVertices; i++)
  {
    if (effectOfVertices[i] > effectOfVertices[maxEffectVertice])
    {
      maxEffectVertice = i;
    }
  }

  if (effectOfVertices[maxEffectVertice] == 0) return -1;

  return maxEffectVertice;
}

void coverVertice(int vertice)
{
  if (isVerticeCovered[vertice]) return;

  isVerticeCovered[vertice] = true;

  // update effect of vertices
  effectOfVertices[vertice] --;

  AdjacencyNode * adjacencyNode = adjacencies[vertice].next;
  while (adjacencyNode != NULL)
  {
    effectOfVertices[adjacencyNode->adjacency] --;

    adjacencyNode = adjacencyNode->next;
  }
}

// return sum of additional effect
int coverAdjacenciesWithPower(int powerPoint, int power, int parentOfPowerPoint)
{
  if (power == 0)
  {
    coverVertice(powerPoint);

    return effectOfVertices[powerPoint];
  }

  int sumOfAdditionalEffect = 0;

  AdjacencyNode * adjacencyNode = adjacencies[powerPoint].next;
  while (adjacencyNode != NULL)
  {
    if (adjacencyNode->adjacency != parentOfPowerPoint)
    {
      sumOfAdditionalEffect += coverAdjacenciesWithPower(adjacencyNode->adjacency, power-1, powerPoint);
    }

    adjacencyNode = adjacencyNode->next;
  }

  return sumOfAdditionalEffect;
}

int main()
{
  input();

  // debug
  for (int i=1; i<=countOfVertices; i++)
  {
    cout << effectOfVertices[i] << ' ';
  }
  cout << endl;

  while (true)
  {
    int maxEffectVertice = pickMaxEffectVertice();

    if (maxEffectVertice == -1) break;

    minSumOfPowers ++;

    powerOfVertices[maxEffectVertice] ++;

    coverVertice(maxEffectVertice);
    effectOfVertices[maxEffectVertice] += coverAdjacenciesWithPower(maxEffectVertice, powerOfVertices[maxEffectVertice], -1);

    // debug
    for (int i=1; i<=countOfVertices; i++)
    {
      cout << effectOfVertices[i] << ' ';
    }
    cout << endl;
  }

  cout << minSumOfPowers << endl;
}
