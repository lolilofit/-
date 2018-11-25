#include<iostream>
#include<fstream>
#ifdef __INTEL_COMPILER
#include<mkl_cblas.h> 
#else
#include<cblas.h> 
#endif

int max_i(float *A, int N) {
	int m = 0, _max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			m += A[i*N+j];

		if (m > _max)
			_max = m;
		m = 0;
	}
	return _max;
}

int max_j(float *A, int N) {
	int m = 0, _max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			m += A[i*N+j];

		if (m > _max)
			_max = m;
		m = 0;
	}
	return _max;
}

int main() {
	int i, j, N, M;
	std::ifstream in;
	in.open("in.txt");
	int N, M;
	in >> N;
	in >> M;
	float* A;
	float* I;
	float* R;
	float* C;
	float* B;
	float* A_rev;
	C = (float*)malloc(N*N * sizeof(float));
	A = (float*)malloc(N*N * sizeof(float));
	I = (float*)malloc(N*N * sizeof(float));
	R = (float*)malloc(N*N * sizeof(float));
	B = (float*)malloc(N*N * sizeof(float));
	A_rev = (float*)malloc(N*N * sizeof(float));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			int val;
			in >> val;
			A[i*N + j] = val;
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if(i==j)
			I[i*N + j] = 1;
			else 
				I[i*N + j] = 0;
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j)
				R[i*N + j] = 1;
			else
				R[i*N + j] = 0;
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j)
				A_rev[i*N + j] = 1;
			else
				A_rev[i*N + j] = 0;
		}
	}
	float num = max_i(A, N)* max_j(A, N);
	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
		N, N, N, 1.0/num, A, N, I, N, 0.0, B, N);

	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
			std::cout << I[i*N + j];
		std::cout << std::endl;
	}
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
			std::cout << C[i*N + j];
		std::cout << std::endl;
	}
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N, -1.0, B, N, A, N, 1.0, R, N);

	for (int i = 1; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++)
				C[j*N+k] = 0;
		}

		//plus(R, C, N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N, 1.0, R, N, I, N, 1.0, C, N);
		for (int j = 2; j <= i; j++) {
			//mult(C, R, C, N);
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
				N, N, N, 1.0, C, N, R, N, 1.0, C, N);
		}
		//plus(C, A_rev, N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N, 1.0, C, N, I, N, 1.0, A_rev, N);
	}

	free(C);
	free(A);
	free(R);
	free(I);
	free(A_rev);
	return 0;
}