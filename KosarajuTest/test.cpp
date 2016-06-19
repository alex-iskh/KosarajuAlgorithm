#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>

void firstTraversal (int** A, int& n, int& cur, std::vector<int>& S, int* P, int& count)	//функция, используемая для первого обхода графа
{
	P[cur] = 1;
	++count;
	for(int i=0; i<n; ++i)
	{
		if ((A[i][cur]>0)&&(P[i]==0))
			firstTraversal (A, n, i, S, P, count);
		++count;
	}
	S.push_back(cur);
	++count;
}

void secondTraversal (int** A, int& n, int& cur, std::vector<int>& S, std::vector<int>* V, int* P, int& count)	//функция, используемая для второго обхода графа
{
	V->push_back(cur);
	P[cur] = 1;
	count+=2;
	for(int j=0; j<n; ++j)
	{
		if ((A[cur][j]>0)&&(P[j]==0))
			secondTraversal (A, n, j, S, V, P, count);
		++count;
	}
}

std::list<std::vector<int>>* kosaraju(int** A, int& n, int& count)	//на вход подается указатель матрицы смежности, число вершин в графе и счетчик числа операций
{
	std::vector<int> S;	//стек, в котором будет сформирован порядок второго обхода
	int* P = new int[n];	//массив, в котором будут храниться информация о пройденных вершинах в первом обходе
	for (int i = 0; i<n; ++i)
	{
		P[i] = 0;
		++count;
	}
	int cur_vertex = 0;	//тут будет храниться текущий индекс вершины графа, с которой был запущен поиск в глубину
	++count;
	while (S.size()<n)	//обход транспонированного графа, формирующий стек S
	{
		firstTraversal (A, n, cur_vertex, S, P, count);
		for (int i = 0; i<n; ++i)
			if(!P[i])
			{
					cur_vertex = i;
					++count;
					break;
			}
	}
	std::list<std::vector<int>>* C = new std::list<std::vector<int>>; //лист компонентов сильной связности
	std::vector<int>* cur_vector; //тут будет храниться текущий компонент сильной связности
	for (int i = 0; i<n; ++i)	//обнуляем P
	{
		P[i] = 0;
		++count;
	}
	while(!S.empty())	//обход графа для составления списка компонент сильной связности
	{
		cur_vertex = S.back();
		S.pop_back();
		count+=2;
		if (P[cur_vertex]==0)
		{
			cur_vector = new std::vector<int>;
			secondTraversal (A, n, cur_vertex, S, cur_vector, P, count);
			C->push_back(*cur_vector);
			++count;
		}
	}
	return C;
}

int main()
{
	const int nmax = 1000;
	srand (time(NULL));
	int* op_count = new int[nmax];
	clock_t start, end;
	double* time_count = new double[nmax];
	int** A;
	std::list<std::vector<int>>* C;
	std::cout<<"Testing is in progress...\n";
	for (int n = 1; n<=nmax; ++n)
	{
		A = new int*[n];
		for (int i = 0; i<n; ++i)
		{
			A[i] = new int[n];
			for (int j = 0; j<n; ++j)
				A[i][j] = rand()%2;
		}
		op_count[n-1] = 0;
		start = clock();
		C = kosaraju(A, n, op_count[n-1]);
		end = clock();
		time_count[n-1] = ((double)end - start)/CLOCKS_PER_SEC;
		delete C;
		delete A;
	}
	std::ofstream res("results.m");
	res<<"VertexNum = 1:"<<nmax<<";\nOperations = [";
	for (int i = 0; i<nmax; ++i)
		res<<op_count[i]<<" ";
	res<<"];\nTime = [";
	for (int i = 0; i<nmax; ++i)
		res<<time_count[i]<<" ";
	res<<"];\nfigure;\nplot(VertexNum, Operations);\nfigure;\nplot(VertexNum, Time)\nfigure;\nplot(VertexNum.^2, Operations);\nfigure;\nplot(VertexNum.^2, Time)\n";
	res.close();
	std::cout<<"Testing completed! Launch results.m to see plots of results of testing.\n";
	system("pause");
	return 0;
}