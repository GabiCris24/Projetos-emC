#include <stdio.h>   // Entrada/saída básica (printf, scanf)
#include <stdlib.h>  // Funções do sistema (system, rand, srand)
#include <string.h>  // Manipulação de strings (strcpy, strlen)
#include <time.h>    // Tempo para gerar números aleatórios (time)
#include <ctype.h>   // Funções para caracteres (toupper)
#include <locale.h>  // Ajustar o idioma do código (setlocale)


// Configurações do jogo-DIRETIVAS
#define LIMPAR "cls"  // Comando para limpar a tela no Windows
#define PAUSA system("pause")  // Pausa o programa no Windows
#define MAX_TENTATIVAS 6   // Número máximo de erros permitidos
#define TAM_PALAVRA 20     // Tamanho máximo de cada palavra
#define MAX_CATEGORIAS 3   // Número de categorias (Tecnologia, Frutas, Países)
#define MAX_PALAVRAS 10    // Máximo de palavras por categoria


// Estrutura para categorias
typedef struct {
    char nome[20];  // Nome da categoria (ex: "Frutas")
    char palavras[MAX_PALAVRAS][TAM_PALAVRA]; // Lista de palavras (ex: "BANANA")
    int total;     // Quantas palavras existem na categoria
} Categoria;

Categoria categorias[MAX_CATEGORIAS]; // Array(Lista) de categorias


// Declaração das Funções/Procedimentos do jogo
void iniciarCategorias();
void mostrarMenu();
void creditos();
void comoJogar();
void jogar();
void desenharForca(int erros);
void resultadoFinal(int ganhou, char *palavra);

int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura caracteres em português
    system("TITLE Jogo da Forca"); 

    iniciarCategorias(); // Preenche as categorias com palavras
    
    int sair = 0; // Controla se o programa deve encerrar
    while (!sair) { // Loop principal - Enquanto sair for falso(= 0)
        system(LIMPAR); // Limpa a tela

        mostrarMenu();  // Exibe o menu
        
        char opcao;
        printf("\n Escolha: ");
        scanf(" %c", &opcao); // Lê a opção do usuário
        
        switch(opcao) { // Executa a opção escolhida
            case '1': jogar(); break;     // Inicia o jogo
            case '2': comoJogar(); break; // Mostra instruções
            case '3': creditos(); break;  // Mostra créditos
            case '4': sair = 1; break;    // Sai do jogo - Quando sair for verdadeiro
            default: // Se digitar algo inválido
                printf("\n Opção inválida!\n");
                PAUSA;   // Espera o usuário pressionar algo
        }
    }

    printf("\n Valeu por jogar! Até mais!:)\n");
    
    return 0; // Encerra o programa
}

void iniciarCategorias() {
    // Tecnologia
    strcpy(categorias[0].nome, "Tecnologia");
    strcpy(categorias[0].palavras[0], "COMPUTADOR");
    strcpy(categorias[0].palavras[1], "PROGRAMACAO");
    strcpy(categorias[0].palavras[2], "ALGORITMO");
    strcpy(categorias[0].palavras[3], "INTERNET");
    categorias[0].total = 4;
    
    // Frutas
    strcpy(categorias[1].nome, "Frutas");
    strcpy(categorias[1].palavras[0], "BANANA");
    strcpy(categorias[1].palavras[1], "MELANCIA");
    strcpy(categorias[1].palavras[2], "LARANJA");
    strcpy(categorias[1].palavras[3], "MORANGO");
    categorias[1].total = 4;
    
    // Países
    strcpy(categorias[2].nome, "Países");
    strcpy(categorias[2].palavras[0], "BRASIL");
    strcpy(categorias[2].palavras[1], "ARGENTINA");
    strcpy(categorias[2].palavras[2], "CANADA");
    strcpy(categorias[2].palavras[3], "JAPAO");
    categorias[2].total = 4;
}

void mostrarMenu() {
   
    printf("\n\t--------------------------------");
    printf("\n\t|                              |");
    printf("\n\t|        JOGO DA FORCA         |");
    printf("\n\t|         ------------         |");
    printf("\n\t|                              |");
    printf("\n\t| 1. Jogar                     |");
    printf("\n\t| 2. Como jogar                |");
    printf("\n\t| 3. Créditos                  |");
    printf("\n\t| 4. Sair                      |");
    printf("\n\t|                              |");
    printf("\n\t--------------------------------");

}

void creditos() {
    system(LIMPAR);
    printf("\n\t-------------------------------");
    printf("\n\t|          CRÉDITOS           |");
    printf("\n\t|-----------------------------|");
    printf("\n\t|                             |");
    printf("\n\t| Feito por: Gabriela Barbosa |");
    printf("\n\t| Disciplina: APC             |");
    printf("\n\t| Professor: Clenio Fonseca   |");
    printf("\n\t|                             |");
    printf("\n\t-------------------------------");

    PAUSA;
}

void comoJogar() {
    system(LIMPAR);
    
    printf("\n\tCOMO JOGAR:");
    printf("\n\t------------------------------------");
    printf("\n \t1. Escolha uma categoria");
    printf("\n\t2. Adivinhe a palavra letra por letra");
    printf("\n\t3. Você tem %d chances", MAX_TENTATIVAS);
    printf("\n\t4. Não repita letras");
    printf("\n\t------------------------------------");
    printf("\n\tDica: Comece pelas vogais (A, E, I, O, U)");
    printf("\n\t------------------------------------");
    
    PAUSA;
}

void jogar() {
    // Escolher categoria
    system(LIMPAR);
   
    printf("\n\tEscolha uma categoria:");
    printf("\n\t----------------------");
   
    
    for (int i = 0; i < MAX_CATEGORIAS; i++) { //Ordena as categorias 0 ate MAX_CATEGORIAS
        printf("\n  %d. %s", i+1, categorias[i].nome); //Ordena em ordem crescente as categorias
    }

    int cat;

    do {
        printf("\nDigite o número: ");
        scanf("%d", &cat);
    } while(cat < 1 || cat > MAX_CATEGORIAS); // Loop caso o usuário digite um número errado
    
    cat--; // Ajusta para índice do array - Decremento das categorias
    
    // Sorteia palavra
    srand(time(NULL));// função que inicializa o gerador de números pseudo-aleatórios do rand() - time(NULL)retorna o tempo atual em segundos 
    char palavra[TAM_PALAVRA];//Declara um array para armazenar a palavra selecionada
    strcpy(palavra, categorias[cat].palavras[rand() % categorias[cat].total]); //O operador % (módulo) pega o resto da divisão por total
    
    // Inicializa jogo
    char palavraOculta[TAM_PALAVRA];//Armazena a palavra a ser descoberta, mostrando apenas as letras acertadas
    char letrasUsadas[26] = {0}; //Registra quais letras já foram tentadas (A-Z)
    int tentativas = 0, acertos = 0;//Conta quantas tentativas (erros) o jogador já deu
    int tamanho = strlen(palavra);//Armazena o comprimento da palavra a ser adivinhada
    
    for (int i = 0; i < tamanho; i++) { //Percorre cada posição da palavra original
        palavraOculta[i] = '_'; //Transforma em '_"
    }
    palavraOculta[tamanho] = '\0'; //marcar o fim da string
    
    // Loop principal
    while (tentativas < MAX_TENTATIVAS && acertos < tamanho) { //Loop caso não atingir o máximo de tentativas e se a palavraOculta não foi preenchida
        system(LIMPAR);
        
        // Cabeçalho
       
        printf("\n\tCategoria: %s", categorias[cat].nome); //Nome da categoria
        printf("\n\tTentativas: %d/%d", MAX_TENTATIVAS - tentativas, MAX_TENTATIVAS); //Número de tentativas
        
        
        // Desenha forca
        desenharForca(tentativas);
        
        // Mostra palavra
        printf("\n  "); //alinha a palavra
        for (int i = 0; i < tamanho; i++) { //Contador do tamanho da palavra
            if (palavraOculta[i] == '_') { //Verifica se o caractere atual é '_' (letra não descoberta)
            } else {
            }
            printf("%c ", palavraOculta[i]); //Imprime o caractere atual da palavra oculta
        }
        
        
        // Letras usadas
        printf("\nLetras usadas: ");
        for (int i = 0; i < 26; i++) { //Percorre todas as 26 letras do alfabeto (A-Z)
            if (letrasUsadas[i]) { //Verifica se a letra correspondente ao i foi usada
                printf("%c ", letrasUsadas[i]); //Se a letra foi usada, imprime o caractere correspondente
            }
        }
        
        // Input do usuário
        char letra;
        printf("\nDigite uma letra: ");
        scanf(" %c", &letra);
        letra = toupper(letra);
        
        // Validação
        if (!isalpha(letra)) { //verifica se o caractere (letra) é uma letra do alfabeto (A-Z ou a-z)
            
            printf("\n\tPor favor, digite uma letra válida!"); //if verdadeiro se não for uma letra
            
            PAUSA;
            continue;
        }
        
        // Verifica se já usou
        if (letrasUsadas[letra - 'A']) { //armazena quais letras já foram tentadas.

            printf("\n\tVocê já tentou esta letra!"); //Se letrasUsadas for verdadeiro (não zero), significa que a letra já foi usada.
           
            PAUSA;
            continue;
        }
        
        letrasUsadas[letra - 'A'] = letra;//Atribui a letra à posição correspondente no array letrasUsadas
        //letra - 'A', está subtraindo o valor ASCII de 'A' (65) do valor ASCII da letra digitada
        // ASCII representa caracteres como números - gera índices de 0 a 25
        
        // Verifica se está na palavra
        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) { //Percorre cada caractere da palavra
            if (palavra[i] == letra) {//se a letra corresponde a palavraOculta
                palavraOculta[i] = letra; // Revela a letra
                acertos++; 
                encontrou = 1; 
            }
        }
        
        if (!encontrou) { //encontrou falso
            tentativas++; 
        }
    }
    
    resultadoFinal(acertos == tamanho, palavra); 
}

void desenharForca(int erros) {

    printf("\n  _______");
    printf("\n  |/     |");
    printf("\n  |     %c%c%c", (erros >= 1 ? '(' : ' '), //condição ? expressão_se_verdadeiro : expressão_se_falso 
                            (erros >= 1 ? '_' : ' '), //cabeça
                            (erros >= 1 ? ')' : ' ')); //cabeça
    printf("\n  |     %c%c%c", (erros >= 3 ? '\\' : ' '), //braço esquerdo
                            (erros >= 2 ? '|' : ' '), //torso
                            (erros >= 4 ? '/' : ' ')); //braço direito
    printf("\n  |      %c", (erros >= 2 ? '|' : ' ')); //torso
    printf("\n  |     %c %c", (erros >= 5 ? '/' : ' '), //perna esquerda
                            (erros >= 6 ? '\\' : ' ')); //perna direita
    printf("\n  |");
    printf("\n _|___");

}

void resultadoFinal(int ganhou, char *palavra) { //ponteiro para o endereço da palavra sorteada, e reproduzindo o conteúdo
    system(LIMPAR);
    
     if (ganhou) {
       
        printf("\n\t****************************************");
        printf("\n\t*                                      *");
        printf("\n\t*           VOCÊ GANHOU!               *");
        printf("\n\t*                                      *");
        printf("\n\t*     A palavra era: %-13s     *", palavra); //alinhamento da palavra para a esquerda (-)
        printf("\n\t*                                      *");
        printf("\n\t****************************************");
    } else {
      
        printf("\n\t########################################");
        printf("\n\t#                                      #");
        printf("\n\t#           VOCÊ PERDEU!               #");
        printf("\n\t#                                      #");
        printf("\n\t#     A palavra era: %-13s     #", palavra); //espaço 13 caracteres
        printf("\n\t#                                      #");
        printf("\n\t########################################");
    }
    
    char opcao;
    printf("\n\tDeseja jogar novamente? (S/N): ");
    scanf(" %c", &opcao);
    
    if (toupper(opcao) == 'S') {
        jogar();
    }
}