#include <iostream>

using namespace std;

int countOfStairs;
int * scores, * maxScoreTill;

void input()
{
  cin >> countOfStairs;

  scores = new int[countOfStairs + 1];
  maxScoreTill = new int[countOfStairs + 1];

  for (int i=1; i<=countOfStairs; i++)
  {
    cin >> scores[i];
  }
}

int pickLarger(int int1, int int2)
{
  return int1 >= int2 ? int1 : int2;
}

int main()
{
  input();

  maxScoreTill[1] = scores[1];
  maxScoreTill[2] = scores[1] + scores[2];
  maxScoreTill[3] = pickLarger(scores[1] + scores[3], scores[2] + scores[3]);

  for (int i=4; i<=countOfStairs; i++)
  {
    maxScoreTill[i] = pickLarger(maxScoreTill[i-2] + scores[i]
        , maxScoreTill[i-3] + scores[i-1] + scores[i]);
  }

  cout << maxScoreTill[countOfStairs] << endl;
}
