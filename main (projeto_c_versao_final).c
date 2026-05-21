#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição do número máximo de cartas para o blackjack
#define MAX_CARTAS 21

// Definição do tipo de struct para jogador do blackjack
typedef struct
{
	int cartas[MAX_CARTAS];
	int quantidade;
	int total;
} Jogador;

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

void limpar_tela()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void linha()
{
	printf("============================================================\n");
}

void titulo(char texto[])
{
	linha();
	printf(" %-58s\n", texto);
	linha();
}

// ============================================================================
// BLACKJACK
// ============================================================================

void comprar_carta(Jogador *j)
{
	int carta = (rand() % 10) + 1;

	j->cartas[j->quantidade] = carta;
	j->quantidade++;
	j->total = j->total + carta;
}

void mostrar_mao(char nome[], Jogador *j)
{
	printf("\n+----------------------------------------------------------+\n");
	printf("| %-56s |\n", nome);
	printf("+----------------------------------------------------------+\n");

	for (int i = 0; i < j->quantidade; i++)
	{
		printf("| Carta %-2d : %-44d |\n", i + 1, j->cartas[i]);
	}

	printf("+----------------------------------------------------------+\n");
	printf("| Total : %-49d |\n", j->total);
	printf("+----------------------------------------------------------+\n");
}

void blackjack()
{
	char option = 's';

	do
	{
		Jogador jogador = {0};
		Jogador oponente = {0};

		int choice = 1;

		comprar_carta(&jogador);
		comprar_carta(&jogador);

		comprar_carta(&oponente);
		comprar_carta(&oponente);

		while (choice == 1 && jogador.total < 21 && oponente.total < 21)
		{
			limpar_tela();

			titulo("BLACKJACK");

			mostrar_mao("OPONENTE", &oponente);
			mostrar_mao("JOGADOR", &jogador);

			if (jogador.total >= 21)
			{
				break;
			}

			printf("\n[1] Pegar carta");
			printf("\n[2] Parar");
			printf("\n\nEscolha: ");
			scanf("%d", &choice);

			if (choice == 1)
			{
				if (oponente.total < 17)
				{
					comprar_carta(&oponente);
				}

				comprar_carta(&jogador);
			}

			while (choice == 2 && oponente.total < jogador.total)
			{
				comprar_carta(&oponente);
			}
		}

		limpar_tela();

		titulo("RESULTADO FINAL");

		mostrar_mao("OPONENTE", &oponente);
		mostrar_mao("JOGADOR", &jogador);

		printf("\n");

		if (jogador.total > 21 && jogador.total != oponente.total)
		{
			printf(">> Você estourou! O oponente venceu.\n");
		}
		else if (oponente.total > 21 && jogador.total != oponente.total)
		{
			printf(">> Seu oponente estourou! Você venceu.\n");
		}
		else if (jogador.total > oponente.total)
		{
			printf(">> Você venceu!\n");
		}
		else if (oponente.total > jogador.total)
		{
			printf(">> Você perdeu.\n");
		}
		else
		{
			printf(">> Ocorreu um empate!\n");
		}

		linha();
		printf("Jogar novamente? (s/n): ");
		scanf(" %c", &option);

	} while (option == 's' || option == 'S');
}

// ============================================================================
// PEDRA PAPEL TESOURA
// ============================================================================

void pedra_papel_tesoura()
{
	int escolha_ppt_pessoal, escolha_ppt_bot;
	int placar_player = 0, placar_bot = 0;
	char option;

	do
	{
		limpar_tela();

		titulo("PEDRA, PAPEL E TESOURA");

		printf("┌──────────────────────────────┐\n");
		printf("│ [1] Pedra                    │\n");
		printf("│ [2] Papel                    │\n");
		printf("│ [3] Tesoura                  │\n");
		printf("└──────────────────────────────┘\n");

		printf("\nPLACAR");
		printf("\n+------------------------------+\n");
		printf("| Você : %-3d                 |\n", placar_player);
		printf("| Bot   : %-3d                 |\n", placar_bot);
		printf("+------------------------------+\n");

		printf("\nDigite sua jogada: ");
		scanf("%d", &escolha_ppt_pessoal);

		escolha_ppt_bot = (rand() % 3) + 1;

		printf("\n");

		switch (escolha_ppt_pessoal)
		{
		case 1:

			switch (escolha_ppt_bot)
			{
			case 1:
				printf("Você: Pedra  x  Bot: Pedra\n");
				printf(">> Empate!\n");
				break;

			case 2:
				printf("Você: Pedra  x  Bot: Papel\n");
				printf(">> Você perdeu!\n");
				placar_bot++;
				break;

			case 3:
				printf("Você: Pedra  x  Bot: Tesoura\n");
				printf(">> Você ganhou!\n");
				placar_player++;
				break;
			}

			break;

		case 2:

			switch (escolha_ppt_bot)
			{
			case 1:
				printf("Você: Papel  x  Bot: Pedra\n");
				printf(">> Você ganhou!\n");
				placar_player++;
				break;

			case 2:
				printf("Você: Papel  x  Bot: Papel\n");
				printf(">> Empate!\n");
				break;

			case 3:
				printf("Você: Papel  x  Bot: Tesoura\n");
				printf(">> Você perdeu!\n");
				placar_bot++;
				break;
			}

			break;

		case 3:

			switch (escolha_ppt_bot)
			{
			case 1:
				printf("Você: Tesoura  x  Bot: Pedra\n");
				printf(">> Você perdeu!\n");
				placar_bot++;
				break;

			case 2:
				printf("Você: Tesoura  x  Bot: Papel\n");
				printf(">> Você ganhou!\n");
				placar_player++;
				break;

			case 3:
				printf("Você: Tesoura  x  Bot: Tesoura\n");
				printf(">> Empate!\n");
				break;
			}

			break;

		default:
			printf(">> Opção inválida!\n");
		}

		linha();
		printf("Jogar novamente? (s/n): ");
		scanf(" %c", &option);

	} while (option == 's' || option == 'S');
}

// ============================================================================
// JOGO DA FORCA
// ============================================================================

void jogo_da_forca()
{
	char option;
	char *palavra_escolhida, input_letra, escolha_palavra, input_palavra[20], progresso[20];

	char lista_palavras[100][20] = {
		"abelha", "abismo", "abobora", "academia", "acampamento",
		"acucar", "adivinho", "agulha", "alface", "algodao",
		"alicate", "almofada", "amarelo", "amizade", "anel",
		"animal", "aranha", "arco", "areia", "arma",
		"arvore", "atleta", "aviao", "banana", "bandeira",
		"barco", "basquete", "batata", "bebida", "beleza",
		"bicicleta", "bloco", "bola", "borracha", "brasil",
		"brinquedo", "cabelo", "cachorro", "cadeira", "caderno",
		"caixa", "camelo", "caminho", "camisa", "caneta",
		"capuz", "carro", "castelo", "cavalo", "celular",
		"cenoura", "chuva", "cidade", "comando", "computador",
		"cozinha", "crianca", "cristal", "cultura", "dado",
		"danca", "desenho", "diamante", "dinheiro", "doce",
		"dragao", "elefante", "energia", "enfermeiro", "escada",
		"escola", "espelho", "estrela", "familia", "fantasia",
		"fazenda", "foguete", "formiga", "futebol", "garrafa",
		"gato", "geleia", "girafa", "guitarra", "helicoptero",
		"igreja", "infinito", "janela", "jardim", "jogador",
		"laranja", "livro", "madeira", "maria", "martelo",
		"monitor", "montanha", "navio", "oceano", "pizza"
	};

	do
	{
		limpar_tela();

		int quantidade_letras = 0;
		int vida = 3;
		int presenca_letra = 0;
		int verificador_letra = 0;
		int vitoria = 0;

		palavra_escolhida = lista_palavras[rand() % 100];

		int i = 0;

		while (palavra_escolhida[i] != '\0')
		{
			quantidade_letras++;
			i++;
		}

		for (int i = 0; i < quantidade_letras; i++)
		{
			progresso[i] = '_';
		}

		progresso[quantidade_letras] = '\0';

		do
		{
			limpar_tela();

			titulo("JOGO DA FORCA");

			printf("VIDAS: ");

			for (int i = 0; i < vida; i++)
			{
				printf("♥ ");
			}

			printf("\n\nPALAVRA (%d letras)\n\n", quantidade_letras);

			for (int i = 0; i < quantidade_letras; i++)
			{
				printf(" %c ", progresso[i]);
			}

			printf("\n\nDigite uma letra: ");
			scanf(" %c", &input_letra);

			for (int i = 0; i < quantidade_letras; i++)
			{
				if (input_letra == palavra_escolhida[i])
				{
					presenca_letra++;
					progresso[i] = input_letra;
				}
			}

			if (presenca_letra > 0)
			{
				printf("\n>> Há %d letra(s) '%c' na palavra!\n",
					   presenca_letra,
					   input_letra);
			}
			else
			{
				vida--;

				printf("\n>> Não há '%c' na palavra!\n", input_letra);
				printf(">> Vida restante: %d\n", vida);
			}

			verificador_letra = 0;

			for (int i = 0; i < quantidade_letras; i++)
			{
				if (progresso[i] == palavra_escolhida[i])
				{
					verificador_letra++;
				}
			}

			if (verificador_letra == quantidade_letras)
			{
				vitoria = 1;
			}

			if (vitoria != 1)
			{
				printf("\nDeseja tentar descobrir a palavra inteira? (s/n): ");
				scanf(" %c", &escolha_palavra);

				switch (escolha_palavra)
				{
				case 's':
				case 'S':

					printf("Digite a palavra: ");
					scanf("%19s", input_palavra);

					verificador_letra = 0;

					for (int i = 0; i < quantidade_letras; i++)
					{
						if (input_palavra[i] != palavra_escolhida[i])
						{
							vida = 0;
							break;
						}

						verificador_letra++;
					}

					if (input_palavra[quantidade_letras] != '\0')
					{
						vida = 0;
					}

					if (verificador_letra == quantidade_letras && vida > 0)
					{
						vitoria = 1;
					}

					break;

				case 'n':
				case 'N':
					break;
				}
			}

			presenca_letra = 0;

			printf("\nPressione ENTER para continuar...");
			getchar();
			getchar();

		} while (vida > 0 && vitoria != 1);

		limpar_tela();

		titulo("RESULTADO");

		if (vitoria == 1)
		{
			printf("\n>> Parabéns! Você descobriu a palavra!\n");
			printf(">> Palavra: %s\n", palavra_escolhida);
		}
		else
		{
			printf("\n>> Você perdeu!\n");
			printf(">> A palavra era: %s\n", palavra_escolhida);
		}

		linha();
		printf("Jogar novamente? (s/n): ");
		scanf(" %c", &option);

	} while (option == 's' || option == 'S');
}

// ============================================================================
// MAIN
// ============================================================================

int main()
{
	srand(time(NULL));

	int menu;

	do
	{
		limpar_tela();

		printf("\n");
		printf("############################################################\n");
		printf("#                                                          #\n");
		printf("#                  CENTRAL DE JOGOS                        #\n");
		printf("#                                                          #\n");
		printf("############################################################\n");

		printf("\n┌──────────────────────────────────────────────────────────┐\n");
		printf("│ [1] Blackjack                                            │\n");
		printf("│ [2] Pedra, Papel e Tesoura                               │\n");
		printf("│ [3] Jogo da Forca                                        │\n");
		printf("│ [0] Sair                                                 │\n");
		printf("└──────────────────────────────────────────────────────────┘\n");

		printf("\nEscolha uma opção: ");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			blackjack();
			break;

		case 2:
			pedra_papel_tesoura();
			break;

		case 3:
			jogo_da_forca();
			break;

		case 0:
			limpar_tela();

			printf("\n");
			printf("============================================================\n");
			printf(" Encerrando programa...\n");
			printf(" Obrigado por jogar!\n");
			printf("============================================================\n");

			break;

		default:
			printf("\n>> Opção inválida!\n");
			printf("Pressione ENTER para continuar...");
			getchar();
			getchar();
			break;
		}

	} while (menu != 0);

	return 0;
}