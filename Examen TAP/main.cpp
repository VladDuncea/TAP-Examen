#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

#pragma region 3 Taskuri in n ore
void afis(vector<int> prev, int poz)
{
	if (poz <= 0)
		return;
	afis(prev, poz - prev[poz]);
	cout << prev[poz] << " ";
}

void task_uri_in_n_ore()
{
	ifstream fin("data.in");


	int n, a, b, c;
	fin >> n >> a >> b >> c;
	vector<int> v(n + 1, -1);
	vector<int> prev(n + 1);
	v[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		if ((i - a >= 0) && v[i - a] != -1 && (v[i - a] + 1 > v[i]))
		{
			v[i] = v[i - a] + 1;
			prev[i] = a;
		}
		if ((i - b >= 0) && v[i - c] != -1 && (v[i - b] + 1 > v[i]))
		{
			v[i] = v[i - b] + 1;
			prev[i] = b;
		}
		if ((i - c >= 0) && v[i - c] != -1 && (v[i - c] + 1 > v[i]))
		{
			v[i] = v[i - c] + 1;
			prev[i] = c;
		}
	}

	cout << v[n] << " ";
	afis(prev,n);
}

#pragma endregion

#pragma region Suma s cu n bancnote

void bancnote()
{
	ifstream fin("data2.in");
	int n,s;
	fin >>s>> n;
	vector<int> v(s + 1, INT_MAX);
	vector<int> bani(n);
	vector<int> prev(s + 1);
	v[0] = 0;
	//citeste bani
	for (int i = 0; i < n;i++)
	{
		fin >> bani[i];
	}

	//incearca sa construieste in v toate sumele pana la s (1,2,..s)
	for (int i = 1; i <= s; i++)
	{
		//incearca la fiecare pas toate bancnotele
		for (int j = 0; j < n; j++)
		{
			//paranteza 1: vezi sa nu incerci sa faci suma i cu o bancnote mai mare de i EX: s=10,bancnota 20, nu exista suma -10
			//paranteza 2: vezi ca suma i - bancnota sa fi putut fi facuta inainte EX: suma 5 nu se poate face din bancotele 3,4 si 8
			//paranteza 3: vezi daca noua suma a fost facuta cu mai putine bancnote
			if ((i - bani[j] >= 0) && v[i - bani[j]] != INT_MAX && (v[i - bani[j]] + 1 < v[i]))
			{
				v[i] = v[i - bani[j]] + 1;
				prev[i] = bani[j];
			}
		}
		
	}

	cout << v[s] << " ";
	afis(prev, s);
}

#pragma endregion

#pragma region Permutari ciclice

void afis1(vector<vector<int>> &data,vector<vector<pair<int, int>>> &prev, pair<int, int> poz)
{
	if (poz == pair<int,int>(-1, -1))
		return;

	afis1(data,prev, prev[poz.first][poz.second]);

	cout << poz.first + 1 << " din S: ";
	for (int i = 0; i < 4; i++)
	{
		cout << data[poz.first][(i + poz.second) % 4]<<" ";
	}
	cout <<"permutare "<<poz.second<< endl;
}

void permut_ciclice()
{
	ifstream fin("data3.in");
	int n;
	fin >> n;
	vector<vector<int>> data(n, vector<int>(4));
	vector<vector<int>> lung(n, vector<int>(4,0));
	vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(4, { -1,-1 }));
	//read permutations
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fin >> data[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			//ia oricare dintre cele 4 permutari
			for (int k = 0; k < 4; k++)
			{
				for (int z = 0; z < 4; z++)
				{
					//verifica compatibilitatea
					if ((data[i][(1 + k) % 4] < data[j][(1 + z) % 4])&& (data[i][(3 + k) % 4] > data[j][(3 + z) % 4]))
					{
						if (lung[i][k] + 1 >= lung[j][z])
						{
							lung[j][z] = lung[i][k] + 1;
							prev[j][z].first = i;
							prev[j][z].second = k;
						}
					}
				}
			}
		}
	}

	int maxim = 0;
	pair<int,int> poz;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (maxim < lung[i][j])
			{
				maxim = lung[i][j];
				poz.first = i;
				poz.second = j;
			}
		}
	}

	//afisare final
	cout << "lungime maxima:" << maxim <<endl;

	//afisare permutari
	afis1(data,prev, poz);

}

#pragma endregion


int main()
{
	permut_ciclice();

	return 0;
}