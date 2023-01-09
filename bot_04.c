// compilador: gcc bot_04.c -o bot_04
// gerenciador: ./uno bot_B bot_04 -s 60529 -v
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

typedef struct {
  char valorCarta[3];
  char naipeCarta[4];
} Carta;

void extract(char card[], Carta vetor[]) {
  int tam;
  tam = strlen(card);

  if (tam == 4) {
    for (int i = 0; i < 30; i++) {
      if (strncmp(vetor[i].valorCarta, "\0", 1) == 0) {
        strncpy(vetor[i].valorCarta, card, 1);
        strncpy(vetor[i].naipeCarta, &card[1], 3);
        break;
      }
    }
  } else {
    for (int i = 0; i < 30; i++) {
      if (strncmp(vetor[i].valorCarta, "\0", 1) == 0) {
        strncpy(vetor[i].valorCarta, card, 2);
        strncpy(vetor[i].naipeCarta, &card[2], 3);
        break;
      }
    }
  }
}

void extractTable(char card[], Carta table[]) {
  int tam;
  tam = strlen(card);

  if (tam == 4) {
    strncpy(table[0].valorCarta, card, 1);
    strncpy(table[0].naipeCarta, &card[1], 3);
  } else {
    strncpy(table[0].valorCarta, card, 2);
    strncpy(table[0].naipeCarta, &card[2], 3);
  }
}

void mudaCor(char complemento2[MAX_LINE], Carta vetor[], Carta table[]) {
  printf("SAY coe mane\n");
  char cartaRecebida[6];
  for (int i = 0; i < 30; i++) {
    if (strcmp(complemento2, vetor[i].naipeCarta) == 0) {
      strcpy(table[0].valorCarta, vetor[i].valorCarta);
      strcpy(table[0].naipeCarta, vetor[i].naipeCarta);
      if (strcmp(vetor[i].valorCarta, "C") == 0 ||
          strcmp(vetor[i].valorCarta, "A") == 0) {
        printf("DISCARD %s%s %s\n", vetor[i].valorCarta, vetor[i].naipeCarta,
               vetor[i].naipeCarta);
      } else {
        printf("DISCARD %s%s\n", vetor[i].valorCarta, vetor[i].naipeCarta);
			}
      memset(vetor[i].valorCarta, '\0', 3);
      memset(vetor[i].naipeCarta, '\0', 4);

      return;
    }
  }

  printf("BUY 1\n");
  scanf(" %s", cartaRecebida);
  extract(cartaRecebida, vetor);
  return;
}

void acaoComprar(Carta table[], Carta vetor[]) {
  printf("SAY Vacilo isso dai\n");

  char cartaRecebida[6];
  if (strstr(table[0].valorCarta, "C") != NULL) {
    printf("BUY 4\n");
    for (int i = 0; i < 4; i++) {
      scanf("%s\n", cartaRecebida);
      extract(cartaRecebida, vetor);
    }
  } else if (strncmp(table[0].valorCarta, "V", 1) == 0) {
    printf("BUY 2\n");
    for (int i = 0; i < 2; i++) {
      scanf("%s\n", cartaRecebida);
      extract(cartaRecebida, vetor);
    }
  }
}

int acaoDescartar(Carta vetor[], Carta table[]) {
  printf("SAY AGORA É COM NOIS\n");

  char cartaComprada[6]; 

  for (int i = 0; i < 30; i++) {
    if (strcmp(table[0].valorCarta, vetor[i].valorCarta) == 0 ||
        strcmp(table[0].naipeCarta, vetor[i].naipeCarta) == 0) {

      if (strcmp(vetor[i].valorCarta, "C") == 0 ||
          strcmp(vetor[i].valorCarta, "A") == 0) {
        printf("DISCARD %s%s %s\n", vetor[i].valorCarta, vetor[i].naipeCarta,
               vetor[i].naipeCarta);
      } else {
        printf("DISCARD %s%s\n", vetor[i].valorCarta, vetor[i].naipeCarta);
      }
      strcpy(table[0].valorCarta, vetor[i].valorCarta);
      strcpy(table[0].naipeCarta, vetor[i].naipeCarta);
      memset(vetor[i].valorCarta, '\0', 3);
      memset(vetor[i].naipeCarta, '\0', 4);
      return 0;
    }
  }
  printf("BUY 1\n");
  scanf(" %s", cartaComprada);
  extract(cartaComprada, vetor);
  return 1;
}

int main() {
  Carta table[1];
  char bots[MAX_LINE];
  char meu_id[MAX_ID_SIZE];
  char card[6];
  Carta cartas[30];
  Carta mesa[1];
  int contador = 0;
  int armazenar;
  memset(meu_id, '\0', 10);
  memset(table[0].valorCarta, '\0', 3);
  memset(table[0].naipeCarta, '\0', 4);
  for (int i = 0; i < 30; i++) {
    memset(cartas[i].valorCarta, '\0', 3);
    memset(cartas[i].naipeCarta, '\0', 4);
  }

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", bots);
  scanf("YOU %s\n", meu_id);
  scanf("HAND [ ");
  while (contador == 0) {
    scanf("%s", card);
    card[0] == ']' ? contador++ : extract(card, cartas);
  }
  scanf("\n");
  scanf("TABLE %s", card);
  extractTable(card, table);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char secondComplement[MAX_LINE];
  int cartaValida = 1;

  while (1) {
    cartaValida = 1;
    do {
      scanf(" %s %s", action, complement);

      if (strcmp(complement, meu_id) != 0) {
        cartaValida = 1;
      }
      if (strcmp(action, "DISCARD") == 0) {
        cartaValida = 0;
        strcpy(card, complement);
        extractTable(card, table);
        if ((strncmp(complement, "A", 1) == 0) ||
            (strncmp(complement, "C", 1) == 0)) {

          scanf(" %s", secondComplement);
          strcpy(table[0].naipeCarta, secondComplement);
        }
      }
    } while (strcmp(action, "TURN") || strcmp(complement, meu_id));

    if (strstr(table[0].valorCarta, "C") != NULL && cartaValida == 0) {
      acaoComprar(table, cartas); 

    } else if (strstr(table[0].valorCarta, "V") != NULL ||
               strcmp(table[0].valorCarta, "V") == 0 && cartaValida == 0) {
      acaoComprar(table, cartas); 
			
    } else if (strstr(table[0].valorCarta, "A") != NULL && cartaValida == 0) {
      strcpy(table[0].naipeCarta, secondComplement);
      mudaCor(secondComplement, cartas, table);

    } else {
      armazenar = acaoDescartar(cartas, table);
    }
  }

  return 0;
}