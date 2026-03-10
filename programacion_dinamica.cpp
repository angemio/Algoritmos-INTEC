#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    int n = s1.size();
    int m = s2.size();

    // matriz DP donde dp[i][j] representa la longitud del LCS
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));

    // Llenar la tabla DP
    // Si los caracteres coinciden, avanzamos diagonalmente
    // Si no coinciden, tomamos el máximo entre izquierda y arriba
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // Reconstrucción de la subsecuencia común más larga
    int i = n;
    int j = m;
    string lcs = "";

    // Retroceder por la tabla DP para recuperar la subsecuencia
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs; // Agregar el carácter al inicio
            i--;
            j--;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) i--;
            else j--;
        }
    }

    // Resultado
    cout << "Longitud: " << dp[n][m] << endl;
    cout << "Subsecuencia: " << lcs << endl;

    return 0;
}