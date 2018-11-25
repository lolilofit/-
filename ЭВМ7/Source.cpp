#include<iostream>
#include<string>
#include<vector>
#include<fstream>

void mult(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> &C, int N) {
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
}

int max_i(std::vector<std::vector<float>> A, int N) {
	int m = 0, _max=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			m += A[i][j];

		if (m > _max)
			_max = m;
		m = 0;
	}
	return _max;
}

int max_j(std::vector<std::vector<float>> A, int N) {
	int m = 0, _max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			m += A[j][i];

		if (m > _max)
			_max = m;
		m = 0;
	}
	return _max;
}

void sub(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> &C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void plus(std::vector<std::vector<float>> A, std::vector<std::vector<float>> &C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] += A[i][j];
		}
	}
}

void div_num(std::vector<std::vector<float>> A, std::vector<std::vector<float>> &C, float a, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			C[i][j] = A[i][j] / a;
	}
}

void transp(std::vector<std::vector<float>> A, std::vector<std::vector<float>> &C, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			C[j][i] = A[i][j];
	}
}

int main(int argc, char* argv[]) {
	std::ifstream in;
	in.open("in.txt");
	int N, M;
	in >> N;
	in >> M;
	std::vector<std::vector<float>> A;
	A.resize(N);
	for (int i = 0; i < N; i++) {
		A[i].resize(N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			in >> A[i][j];
	}


	std::vector<std::vector<float>> I;
	I.resize(N);
	for (int i = 0; i < N; i++) {
		I[i].resize(N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)
				I[i][j] = 1;
		}
	}


	std::vector<std::vector<float>> B;
	B.resize(N);
	for (int i = 0; i < N; i++) {
	B[i].resize(N);
	}
	std::vector<std::vector<float>> R;
	R.resize(N);
	for (int i = 0; i < N; i++) {
		R[i].resize(N);
	}
	std::vector<std::vector<float>> C;
	C.resize(N);
	for (int i = 0; i < N; i++) {
		C[i].resize(N);
	}
	std::vector<std::vector<float>> A_rev;
	A_rev.resize(N);
	for (int i = 0; i < N; i++) {
		A_rev[i].resize(N);
	}
	transp(A, B, N);
	float num = max_i(A, N)* max_j(A, N);
	div_num(B, B, num, N);
	mult(B, A, C, N);
	//mult_num(B, C, -1, N);
	sub(I, C, R, N);
	plus(I, A_rev, N);

	for (int i = 1; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++)
				C[j][k] = 0;
		}
		
		plus(R, C, N);
		for (int j = 2; j <= i; j++) {
			mult(C, R, C, N);
		}
		plus(C, A_rev, N);
	}
	mult(A_rev, B, A_rev, N);
	in.close();
	return 0;
}