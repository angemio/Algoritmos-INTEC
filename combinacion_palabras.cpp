#include<bits/stdc++.h>
using namespace std;
void permutations(string s, string ans){
    if(s.size() == 0) {
    // cuando el string que necesita ser rotado
    // esta vacio, entonces significa
    // que nuestra permutacion se almacena en "ans"
        cout << ans << "\n";
        return ;
    }
    for(int i = 0; i < s.size(); i++){
        // s.substr(1) pasamos el string sin el primer caracter
        // ans + s[0] agregamos el primer caracter actual a nuestra respuesta acumulada
        permutations(s.substr(1), ans + s[0]);
      
        rotate(s.begin(), s.begin()+1, s.end());
        // rotamos para que el caracter que estaba primero pase al final
        // esto permite que en la proxima iteracion, el siguiente caracter
        // (que ahora es el primero) sea elegido
    }
}
int main(){
    string s = "Hola";
    permutations(s, "");
    return 0;
}