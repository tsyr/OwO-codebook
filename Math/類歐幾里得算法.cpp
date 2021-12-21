\sum_{i = 0}^{N - 1} floor((A \times i + B) / M).
ll f(int n, int a, int b, int c) {
	if (!a) return (b / c) * (n + 1);
	if (a >= c || b >= c)
		return f(n, a % c, b % c, c) + (ll) n * (n + 1) / 2 * (a / c) + (ll) (n + 1) * (b / c);
	int m = ((ll) a * n + b) / c;
	return (ll) n * m - f(m - 1, c, c - b - 1, a);
}
