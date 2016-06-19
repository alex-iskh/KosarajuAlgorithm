#include <vector>
#include <list>
#include <stack>
#include <iostream>

void firstTraversal (int** A, int& n, int& cur, std::vector<int>& S, int* P)	//функция, используемая для первого обхода графа
{
	P[cur] = 1;
	for(int i=0; i<n; ++i)
		if ((A[i][cur]>0)&&(P[i]==0))
			firstTraversal (A, n, i, S, P);
	S.push_back(cur);
}

void secondTraversal (int** A, int& n, int& cur, std::vector<int>& S, std::vector<int>* V, int* P)	//функция, используемая для второго обхода графа
{
	V->push_back(cur);
	P[cur] = 1;
	for(int j=0; j<n; ++j)
		if ((A[cur][j]>0)&&(P[j]==0))
			secondTraversal (A, n, j, S, V, P);
}

std::list<std::vector<int>>* kosaraju(int** A, int& n)	//на вход подается указатель матрицы смежности и число вершин в графе
{
	std::vector<int> S;	//стек, в котором будет сформирован порядок второго обхода
	int* P = new int[n];	//массив, в котором будут храниться информация о пройденных вершинах в первом обходе
	for (int i = 0; i<n; ++i)
		P[i] = 0;
	int cur_vertex = 0;	//тут будет храниться текущий индекс вершины графа, с которой был запущен поиск в глубину
	while (S.size()<n)	//обход транспонированного графа, формирующий стек S
	{
		firstTraversal (A, n, cur_vertex, S, P);
		for (int i = 0; i<n; ++i)
			if(!P[i])
			{
					cur_vertex = i;
					break;
			}
	}
	std::list<std::vector<int>>* C = new std::list<std::vector<int>>; //лист компонентов сильной связности
	std::vector<int>* cur_vector; //тут будет храниться текущий компонент сильной связности
	for (int i = 0; i<n; ++i)	//обнуляем P
		P[i] = 0;
	while(!S.empty())	//обход графа для составления списка компонент сильной связности
	{
		cur_vertex = S.back();
		S.pop_back();
		if (P[cur_vertex]==0)
		{
			cur_vector = new std::vector<int>;
			secondTraversal (A, n, cur_vertex, S, cur_vector, P);
			C->push_back(*cur_vector);
		}
	}
	return C;
}

int main()
{
	int n;
	std::cout<<"n=";
	std::cin>>n;
	std::cout<<"\nAdjacency matrix:\n";
	int** A = new int*[n];
	for (int i = 0; i<n; ++i)
	{
		A[i] = new int[n];
		for (int j = 0; j<n; ++j)
			std::cin>>A[i][j];
	}
	std::cout<<"\nComponents:\n";
	std::list<std::vector<int>>* C = kosaraju(A, n);
	for (std::list<std::vector<int>>::iterator it = C->begin(); it!=C->end(); ++it)
	{
		for(int i = 0; i<(*it).size(); ++i)
			std::cout<<(*it)[i]+1<<" ";
		std::cout<<"\n";
	}
	system("pause");
	return 0;
}