#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	int x;
	int n1;
	int n2;
	const int N = 100;
	vector<int> segments;
	in >> x >> n1 >> n2;
	int tmp;
	in >> tmp;
	while (tmp != 0)
	{
		segments.push_back(tmp);
		in >> tmp;
	}
	vector<vector<int>> matrix(N + 1);
	queue<pair<pair<int, int>, int>> dots;
	for (int i = 0; i < N + 1; i++)
	{
		matrix.at(i).resize(N + 1, -1);
	}
	dots.push(make_pair(make_pair(n1, n2), 0));
	while (!dots.empty())
	{
		auto dot = dots.front().first;
		int weight = dots.front().second;
		dots.pop();
		if (matrix.at(dot.first).at(dot.second) != -1)
		{
			continue;
		}
		matrix.at(dot.first).at(dot.second) = weight;
		// перелить всё
		// из первой
		dots.push(make_pair(make_pair(0, dot.second + dot.first), weight + 1));
		dots.push(make_pair(make_pair(0, dot.second), weight + 1));
		// из второй
		dots.push(make_pair(make_pair(dot.first + dot.second, 0), weight + 1));
		dots.push(make_pair(make_pair(dot.first, 0), weight + 1));
		// из третьей
		dots.push(make_pair(make_pair(dot.first + (N - dot.first - dot.second), dot.second), weight + 1));
		dots.push(make_pair(make_pair(dot.first, (N - dot.first - dot.second) + dot.second), weight + 1));
		for (int i = 0; i < segments.size(); i++)
		{
			// перелить до деления
			// из первой
			if (dot.first > segments.at(i))
			{
				dots.push(make_pair(make_pair(segments.at(i), dot.second + (dot.first - segments.at(i))), weight + 1));
				dots.push(make_pair(make_pair(segments.at(i), dot.second), weight + 1));
			}
			// из второй
			if (dot.second > segments.at(i))
			{
				dots.push(make_pair(make_pair(dot.first + (dot.second - segments.at(i)), segments.at(i)), weight + 1));
				dots.push(make_pair(make_pair(dot.first, segments.at(i)), weight + 1));
			}
			// долить до деления
			// в первую
			if (dot.first < segments.at(i))
			{
				if (dot.second - (segments.at(i) - dot.first) > 0)
				{
					dots.push(make_pair(make_pair(segments.at(i), dot.second - (segments.at(i) - dot.first)), weight + 1));
				}
				if (((N - dot.second - dot.first) - (segments.at(i) - dot.first)) > 0)
				{
					dots.push(make_pair(make_pair(segments.at(i), dot.second), weight + 1));
				}
			}
			// во вторую
			if (dot.second < segments.at(i))
			{
				if (dot.first - (segments.at(i) - dot.second) > 0)
				{
					dots.push(make_pair(make_pair(dot.first - (segments.at(i) - dot.second), segments.at(i)), weight + 1));
				}
				if (((N - dot.second - dot.first) - (segments.at(i) - dot.second)) > 0)
				{
					dots.push(make_pair(make_pair(dot.first, segments.at(i)), weight + 1));
				}
			}

		}
	}
	int result = INT_MAX;
	int need = 100 - x;
	for (int i = 0; i <= need; i++)
	{
		if (matrix.at(i).at(need - i) != -1)
		{
			if (result > matrix.at(i).at(need - i))
			{
				result = matrix.at(i).at(need - i);
			}
		}
	}
	out << ((result == INT_MAX) ? "No solution" : to_string(result)) << endl;
	//for (int i = 0; i < N + 1; i++)
	//{
	//	for (int j = 0; j < (N + 1 - i); j++)
	//	{
	//		cout << setw(3) << matrix[i][j];
	//	}
	//	cout << endl;
	//}




//	system("pause");
	return 0;
}