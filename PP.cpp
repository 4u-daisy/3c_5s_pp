#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <omp.h>

/// <summary>
/// mulls matrix
/// </summary>
/// <param name="_matrOne"> first matr</param>
/// <param name="_matrTwo"> second matr</param>
/// <returns> res matr</returns>
std::vector<std::vector<int>> MullMatrix(std::vector<std::vector<int>> _matrOne, 
	std::vector<std::vector<int>> _matrTwo) 
{
	if (_matrOne.empty() || _matrTwo.empty() || _matrOne[0].size() != _matrTwo.size())
		return std::vector<std::vector<int>>();

	size_t rows = _matrOne.size();
	size_t columns = _matrTwo[0].size();

	std::vector<std::vector<int>> _matrRes(rows);
	
	for (auto i = 0; i < columns; i++) {
		_matrRes[i].resize(columns);
	}

	int threadsNum = 8;
	omp_set_num_threads(threadsNum);
	int i, j, k;
#pragma omp parallel for shared(_matrOne, _matrTwo, _matrRes) private(i, j, k)
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			_matrRes[i][j] = 0;
			for (k = 0; k < _matrTwo.size(); k++) {
				_matrRes[i][j] += _matrOne[i][k] * _matrTwo[k][j];
			}
		}
	}

	return _matrRes;
}

/// <summary>
/// create a random matrix
/// </summary>
/// <param name="rows"></param>
/// <param name="columns"></param>
/// <returns>random matrix</returns>
std::vector<std::vector<int>> CreateRandomMatrix(int rows = 10, int columns = 10) {
	std::vector<std::vector<int>> _matr(rows);
	for (auto i = 0; i < columns; i++) {
		_matr[i].resize(columns);
	}

	for (auto i = 0; i < rows; i++) {
		for (auto j = 0; j < columns; j++) {
			_matr[i][j] = rand() % 20;
		}
	}

	return _matr;
}

/// <summary>
/// writing matrix to file
/// </summary>
/// <param name="_matr"></param>
/// <param name="_path"></param>
/// <returns>result of operation</returns>
bool WritingToFile(std::vector<std::vector<int>> _matr, 
	std::string _path = "matrices.txt") {
	
	if (_matr.size() == 0 || _matr[0].size() == 0)
		return true;

	std::ofstream out(_path);

	if (out.is_open()) {
		auto rows = _matr.size();
		auto columns = _matr[0].size();

		out << rows << " " << columns << std::endl;

		for (auto i = 0; i < rows; i++) {
			for (auto j = 0; j < columns; j++) {
				out << _matr[i][j] << " ";
			}
			out << std::endl;
		}
	}
	else {
		return false;
	}

	out.close();
	return true;
}

/// <summary>
/// Read file
/// </summary>
/// <param name="_matr"></param>
/// <param name="_path"></param>
/// <returns>matrix</returns>
std::vector<std::vector<int>> ReadingFromFile(std::string _path = "matrices.txt") {

	std::vector<std::vector<int>> _matrRes(0);

	std::ifstream in(_path);

	if (in.is_open()) {
		int rows = 0, columns = 0;

		in >> rows >> columns;
		_matrRes.resize(rows);
		for (auto i = 0; i < rows; i++) {
			_matrRes[i].resize(columns);

			for (auto j = 0; j < columns; j++) {
				in >> _matrRes[i][j];
			}
		}
	}

	in.close();
	return _matrRes;
}

/// <summary>
/// Print to Matrix
/// </summary>
/// <param name="_matr"></param>
void PrintMatrix(const std::vector<std::vector<int>> _matr) {
	std::cout << "Your matrix:\n";

	for (auto i = 0; i < _matr.size(); i++) {
		for (auto j = 0; j < _matr[0].size(); j++) {
			std::cout << _matr[i][j] << " ";
		}
		std::cout << std::endl;
	} 
}


int main() {

	const int SIZE = 2500;

	std::vector<std::vector<int>> a = CreateRandomMatrix(SIZE, SIZE);
	std::vector<std::vector<int>> b = CreateRandomMatrix(SIZE, SIZE);

	clock_t start = clock();
	MullMatrix(a, b);
	clock_t end = clock();

	auto res = (double)(end - start)/CLOCKS_PER_SEC;

	std::ofstream result;
	result.open("result2.txt", std::ios::app);
	
	//result << "Size: Result: Count threads:" << std::endl;
	result << SIZE << " " << res << " " << 8 << std::endl;
	result.close();

	std::cout << res << std::endl;
	std::cout << "Okay :)";
}

/*
	std::vector<std::vector<int>> a = CreateRandomMatrix();
	std::vector<std::vector<int>> b = CreateRandomMatrix();

	WritingToFile(a, "a.txt");
	WritingToFile(b, "b.txt");

	std::vector<std::vector<int>> c = MullMatrix(a ,b);

	WritingToFile(c, "c.txt");
*/