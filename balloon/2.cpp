#include <iostream>

using namespace std;

int countOfTeams = -1;
int * dA, * dB, * dD, * k;
bool * isTeamProcessed;

int countOfBalloonsInA = -1, countOfBalloonsInB = -1;

int minTotalDistance = 0;

void input()
{
  cin >> countOfTeams >> countOfBalloonsInA >> countOfBalloonsInB;

  if (countOfTeams == 0) return;

  dA = new int[countOfTeams+1];
  dB = new int[countOfTeams+1];
  dD = new int[countOfTeams+1];
  k = new int[countOfTeams+1];

  isTeamProcessed = new bool[countOfTeams+1];

  for (int i=1; i<=countOfTeams; i++)
  {
    cin >> k[i] >> dA[i] >> dB[i];

    dD[i] = dA[i] >= dB[i] ? dA[i] - dB[i] : dB[i] - dA[i];
  }
}

int pickMaxDDTeam()
{
  int maxDDTeam = 1;

  for (int i=2; i<=countOfTeams; i++)
  {
    if (dD[i] > dD[maxDDTeam])
    {
      maxDDTeam = i;
    }
  }

  // cout << "maxDDTeam: " << maxDDTeam;

  return maxDDTeam;
}

void deliverBalloonsToTeam(int team)
{
  // if closer to A
  if (dA[team] - dB[team] <= 0)
  {
    // if balloons in A are enough
    if (countOfBalloonsInA >= k[team])
    {
      countOfBalloonsInA -= k[team];
      minTotalDistance += dA[team] * k[team];
    }
    else
    {
      countOfBalloonsInB -= k[team] - countOfBalloonsInA;
      minTotalDistance += dB[team] * (k[team] - countOfBalloonsInA);

      minTotalDistance += dA[team] * countOfBalloonsInA;
      countOfBalloonsInA = 0;
    }
  }
  else
  {
    // if balloons in B are enough
    if (countOfBalloonsInB >= k[team])
    {
      countOfBalloonsInB -= k[team];
      minTotalDistance += dB[team] * k[team];
    }
    else
    {
      countOfBalloonsInA -= k[team] - countOfBalloonsInB;
      minTotalDistance += dA[team] * (k[team] - countOfBalloonsInB);

      minTotalDistance += dB[team] * countOfBalloonsInB;
      countOfBalloonsInB = 0;
    }
  }
}

void reset()
{
  countOfTeams = -1;

  delete [] dA;
  delete [] dB;
  delete [] dD;
  delete [] k;

  delete [] isTeamProcessed;

  countOfBalloonsInA = -1;
  countOfBalloonsInB = -1;

  minTotalDistance = 0;
}

int main()
{
  while (true)
  {
    input();

    if (countOfTeams == 0) break;

    for (int i=0; i<countOfTeams; i++)
    {
      int maxDDTeam = pickMaxDDTeam();

      deliverBalloonsToTeam(maxDDTeam);

      isTeamProcessed[maxDDTeam] = true;
      dD[maxDDTeam] = -1;

      // cout << " cA: " << countOfBalloonsInA << " cB: " << countOfBalloonsInB << "\ttotalDistance: " << minTotalDistance << endl;
    }

    cout << minTotalDistance << endl;

    reset();
  }

  return 0;
}
