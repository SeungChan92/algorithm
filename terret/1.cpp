#include <iostream>

using namespace std;

int main()
{
  int t = 0;

  cin >> t;

  for (int i=0; i<t; i++)
  {
    int count = -2;

    int x1, y1, r1, x2, y2, r2;

    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    int diffOfR, sumOfR, distance;

    diffOfR = (r1-r2) * (r1-r2);
    sumOfR = (r1+r2) * (r1+r2);
    distance = (x2-x1) * (x2-x1) + (y2-y1) * (y2-y1);

    if (distance < diffOfR) count = 0;
    else if (distance == diffOfR)
    {
      if (diffOfR == 0) count = -1;
      else count = 1;
    }
    else if (distance < sumOfR) count = 2;
    else if (distance == sumOfR) count = 1;
    else count = 0;

    cout << count << endl;
  }
}
