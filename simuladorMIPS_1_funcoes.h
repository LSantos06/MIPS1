#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MEM_SIZE 4096

/* Memoria */
int32_t mem[MEM_SIZE];

/* Carrega o arquivo data.bin na memoria */
void loadData(FILE *ponteiroArquivo);

/* Carrega o arquivo text.bin na memoria */
void loadText(FILE *ponteiroArquivo);
/******************************************************************************/

/* Leitura */
/* Lê um inteiro alinhado - endereços múltiplos de 4 */
int32_t lw(uint32_t endereco, int16_t deslocamento);

/* Lê meia palavra, 16 bits - retorna inteiro com sinal */
int32_t lh(uint32_t endereco, int16_t deslocamento);

/* Lê um byte - retorna inteiro com sinal */
int32_t lb(uint32_t endereco, int16_t deslocamento);

/* Lê meia palavra, 16 bits - retorna inteiro sem sinal */
int32_t lhu(uint32_t endereco, int16_t deslocamento);

/* Lê um byte - retorna inteiro sem sinal */
int32_t lbu(uint32_t endereco, int16_t deslocamento);
/******************************************************************************/

/* Escrita */
/* Escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
void sw(uint32_t endereco, int16_t deslocamento, int32_t dado);

/* Escreve meia palavra, 16 bits - endereços múltiplos de 2 */
void sh(uint32_t endereco, int16_t deslocamento, int16_t dado);

/* Escreve um byte na memória */
void sb(uint32_t endereco, int16_t deslocamento, int8_t dado);

/******************************************************************************/
/* Menu */
/* Menu de interação com o usuário */
void menu ();
