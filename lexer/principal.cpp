#include "scanner.h"
#include "token.h"

string tokenName(int name) {
    switch (name) {
        case UNDEF: return "UNDEF";
        case ID: return "ID";
        case INTEGER: return "INTEGER";
        case OP: return "OP";
        case SEP: return "SEP";
        case SYSTEM_OUT_PRINTLN: return "SYSTEM_OUT_PRINTLN";
        case END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[]) 
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    string input;
    
    //O trecho a seguir está comentado porque o programa espera receber o nome do arquivo como 
    // argumento na linha de comando, e não ler o código-fonte diretamente do teclado.

    //getline(cin, input); 

    Scanner* scanner = new Scanner(argv[1]);
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        string name = tokenName(t->name);
        // Mostra o lexema entre parênteses para tokens relevantes
        if (t->name == SYSTEM_OUT_PRINTLN)
            cout << name << " ";
        else if (t->name == ID || t->name == INTEGER)
            cout << name << "(" << t->lexeme << ") ";
        else if (t->name == SEP || t->name == OP)
            cout << name << "(" << t->lexeme << ") ";
        else if (t->name == UNDEF)
            cout << name << "(" << t->lexeme << ") ";
        else
            cout << name << " ";
    }while (t->name != END_OF_FILE);

    delete scanner;
    
    return 0;
}