#include <iostream>
#include <climits>
#include <iomanip>

auto RabinKarpMatcher(char T[], char P[], int d, int q) {
    int n = strlen(T); // length of text
    int m = strlen(P); // length of pattern

    int h = 1;

    // calculating h = d^(m-1) mod q
    for (int i = 0; i < m - 1; ++i) {
        h = (h * d) % q;
    }

    int p = 0;
    int t = 0;

    for (int i = 0; i < m; ++i) { // calculating value of pattern and t_0
        p = (d * p + P[i]) % q; // p = P[0 .. m-1] mod q
        t = (d * t + T[i]) % q; // t = T[0 .. m-1] mog q
    }

    // calculating windows t_S mod q and checking if its equal to p
    for (int s = 0; s < n - m + 1; ++s) {
        if (p == t) { // window and pattern mod q are equal
            int j = 0;
            // comparison char by char
            for (; j < m; ++j) {
                if (P[j] != T[s + j]) { // pattern and t_S differ
                    break;
                }
            }
            if (j == m) { // pattern and t are equal
                std::cout << "Found match at position: " << s << std::endl;
            }
        }
        if (s < n - m) { // calculating new t witch is current 
            // window without most significant digit shifted right by one
            t = (d * (t - T[s] * h) + T[s + m]) % q;
            if (t < 0) { // make sure t is positive
                t = t + q;
            }
        }
    }
}

int main()
{
    char pattern[] = {"abc"};
    char text[] = { "dabcefgabc" };

    std::cout << std::setw(10) << "Index:";
    for (int i = 0; i < strlen(text); ++i) {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;
    std::cout << std::setw(10) << "Text:";
    for (int i = 0; i < strlen(text); ++i) {
        std::cout << std::setw(3) << text[i];
    }
    std::cout << std::endl;

    std::cout << std::setw(10) << "Pattern:";
    std::cout << ' ' <<  pattern;
    std::cout << std::endl << std::endl;
    RabinKarpMatcher(text, pattern, 256, 31);
}
