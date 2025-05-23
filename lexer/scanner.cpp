#include "scanner.h"    

// Pronto
//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    // cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;

    //Consumir espaços em branco
    while (isspace(input[pos]))
        pos++;

    // Ignorar comentários
    while (input[pos] == '/')
    {
        if (input[pos + 1] == '/') // Comentário de linha
        {
            pos += 2;
            while (input[pos] != '\n' && input[pos] != '\0')
                pos++;
            if (input[pos] == '\n') pos++;
            while (isspace(input[pos])) pos++; // Ignora espaços após comentário
        }
        else if (input[pos + 1] == '*') // Comentário de bloco
        {
            pos += 2;
            while (!(input[pos] == '*' && input[pos + 1] == '/') && input[pos] != '\0')
            {
                if (input[pos] == '\n') line++; // Atualiza linha se necessário
                
                pos++;
            }
            if (input[pos] == '*' && input[pos + 1] == '/')
                pos += 2;
            while (isspace(input[pos])) pos++; // Ignora espaços após comentário
        }
        else
        {
            break; // Não é comentário, pode ser operador '/'
        }
    }

    //Verificar os tokens possíveis
    //Fim de arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }
    // Verifica System.out.println
    else if (input.compare(pos, 18, "System.out.println") == 0)
    {
        tok = new Token(SYSTEM_OUT_PRINTLN, "System.out.println");
        pos += 18;
    }
    //Identificadores
    else if (isalpha(input[pos]))
    {
        lexeme = "";
        while (isalnum(input[pos]))
        {
            lexeme += input[pos];
            pos++;
            if (input[pos] == '\n') line++;
        }
        tok = new Token(ID, lexeme);
    }
    //Números
    else if (isdigit(input[pos]))
    {
        lexeme = "";
        while (isdigit(input[pos]))
        {
            lexeme += input[pos];
            pos++;
            if (input[pos] == '\n') line++;
        }
        tok = new Token(INTEGER, lexeme);
    }
    //Operadores
    else if (input[pos] == '+' || input[pos] == '-' || 
             input[pos] == '*' || input[pos] == '/' || 
             input[pos] == '=' || input[pos] == '<' || 
             input[pos] == '>' || input[pos] == '!')
    {
        lexeme = "";
        lexeme += input[pos];
        pos++;
        if (input[pos] == '\n') line++;
        tok = new Token(OP, lexeme);
    }
    //Separadores
    else if (input[pos] == '(' || input[pos] == ')' || 
             input[pos] == '{' || input[pos] == '}' || 
             input[pos] == '[' || input[pos] == ']' || 
             input[pos] == ';' || input[pos] == ',')
    {
        lexeme = "";
        lexeme += input[pos];
        pos++;
        if (input[pos] == '\n') line++;
        tok = new Token(SEP, lexeme);
    }
    //Caso não seja nenhum dos tokens acima
    else
    {
        lexeme = "";
        lexeme += input[pos];
        pos++;
        if (input[pos] == '\n') line++;
        tok = new Token(UNDEF, lexeme);
        lexicalError("Token indefinido: " + lexeme);
    }
    return tok;
 
}

void 
Scanner::lexicalError(string msg)
{
    cout << "\n\nLinha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
