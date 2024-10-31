
int Factorial(int n) {

	if (n < 2) {

		return 1;

	}

	return n * Factorial(n - 1);

}

float Power(float t, int n) {

	if (n < 1) {

		return 1.0f;

	}

	return t * Power(t, n - 1);

}

int Binomial(int n, int k) {

	return Factorial(n) / (Factorial(k) * Factorial(n - k));

}

float Bernstein(int n, int i, float t) {

	return static_cast<float>(Binomial(n, i)) * Power(t, i) * Power(1 - t, n - i);

}
