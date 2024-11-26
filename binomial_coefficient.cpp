#include <iostream>
#include <vector>
#include <ctime> // For timing in pre-C++11
#include <iomanip> // For formatting output

// Define macros for maximum values of n and k
#define MAX_N 30

class BinomialCalculator {
public:
    // Constructor to initialize the calculator
    BinomialCalculator(const std::string& name, int (*calcMethod)(int, int))
        : methodName(name), method(calcMethod), computeTimeMs(0) {
        precompute(); // Perform computations during initialization
    }

    // Getter to retrieve precomputed value of C(n, k)
    int get(int n, int k) const {
        if (n <= MAX_N && k <= n) {
            return results[n][k];
        }
        throw std::out_of_range("n or k is out of range");
    }

    // Getter to retrieve computation time
    long long computeTime() const {
        return computeTimeMs;
    }

    // Getter to retrieve the method name
    std::string getName() const {
        return methodName;
    }

    // diplays one row of the precomputed values
    void displayRow(int n) const {
        std::cout << "n = " << std::setw(2) << n << ":\t";
        for (int k = 0; k <= n; ++k) {
            std::cout << results[n][k] << "\t";
        }
        std::cout << "\n";
    }

    // Display the precomputed values
    void displayResults() const {
        std::cout << methodName << " Results:\n";
        for (int n = 1; n <= MAX_N; ++n) {
            displayRow(n);
        }
        std::cout << methodName << " took " << computeTimeMs << " ms\n\n";
    }

private:
    std::string methodName;                   // Name of the calculation method
    int (*method)(int, int);                  // Function pointer to the calculation method
    std::vector<std::vector<int> > results;   // 2D vector to store results
    long long computeTimeMs;                  // Time taken to compute all values

    // Precompute all values of C(n, k) for n = 1..MAX_N and k = 0..n
    void precompute() {
        results.resize(MAX_N + 1);
        for (int n = 0; n <= MAX_N; ++n) {
            results[n].resize(n + 1, 0);
        }

        std::clock_t start = std::clock();

        for (int n = 0; n <= MAX_N; ++n) {
            for (int k = 0; k <= n/2; ++k) { // Compute only half of the values (C(n, k) = C(n, n - k))
                results[n][k] = method(n, k);
                results[n][n - k] = results[n][k]; // C(n, k) = C(n, n - k)
            }
        }

        std::clock_t end = std::clock();
        computeTimeMs = (end - start) * 1000 / CLOCKS_PER_SEC;
    }
};

// Recursive method
int binom_rec(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binom_rec(n - 1, k - 1) + binom_rec(n - 1, k);
}

// Dynamic Programming method
int binom_dp(int n, int k) {
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(k + 1, 0));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= std::min(i, k); ++j) {
            if (j == 0 || j == i)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp[n][k];
}

// Formula method
int factorial(int num) {
    int result = 1;
    for (int i = 2; i <= num; ++i)
        result *= i;
    return result;
}

int binom_formula(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    // Create objects for each calculation method
    BinomialCalculator recursiveCalc("Recursive", binom_rec);
    BinomialCalculator dpCalc("Dynamic Programming", binom_dp);
    BinomialCalculator formulaCalc("Formula", binom_formula);

    // Display precomputed results for each method
    recursiveCalc.displayResults();
    dpCalc.displayResults();
    formulaCalc.displayResults();

    // Example usage of getters
    std::cout << "C(10, 5) using Dynamic Programming: " << dpCalc.get(10, 5) << "\n";
    std::cout << "Time taken by Formula: " << formulaCalc.computeTime() << " ms\n";

    return 0;
}
