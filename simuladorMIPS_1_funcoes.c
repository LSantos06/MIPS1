#include "simuladorMIPS_1_funcoes.h"

/* Memoria */
/* Carrega o arquivo data.bin na memoria */
void loadData(FILE *ponteiroArquivo){
    /* Inicia no 0x00002000, 2048 em decimal */
    uint32_t endereco = 2048;

    /* Percorre o arquivo e armazena na memoria */
    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}

/* Carrega o arquivo text.bin na memoria */
void loadText(FILE * ponteiroArquivo){
    /* Inicia no 0x00000000, 0 em decimal */
    uint32_t endereco = 0;

    /* Percorre o arquivo e armazena na memoria */
    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}
/******************************************************************************/

/* Leitura */
/* Lê um inteiro alinhado - endereços múltiplos de 4 */
int32_t lw(uint32_t endereco, int16_t deslocamento){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("lw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4), erro:\n");
        return -2;
    }

    /* Retorna o valor armazenado no endereco + deslocamento */
    return mem[(endereco + deslocamento)/4];
}

/* Lê meia palavra, 16 bits - retorna inteiro com sinal */
int32_t lh(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;
    int32_t bitMaisSiginificativo[1];

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo os bits mais significativos */
    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0xf0000000;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        /* Se a meia palavra negativa */
        if(bitMaisSiginificativo[0] >= 0x00008000){
            return (mem[novoEndereco] | 0xffff0000);
        }
        /* Se a meia palavra for positiva */
        return (mem[novoEndereco] & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* Se a meia palavra negativa */
        if(bitMaisSiginificativo[1] >= 0x80000000){
            return ((mem[novoEndereco] >> 16) | 0xffff0000);
        }
        /* Se a meia palavra for positiva */
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }
}

/* Lê um byte - retorna inteiro com sinal */
int32_t lb(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;
    int32_t bitMaisSiginificativo[3];

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo os bits mais significativos */
    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x000000f0;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[2] = mem[novoEndereco] & 0x00f00000;
    bitMaisSiginificativo[3] = mem[novoEndereco] & 0xf0000000;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[0] >= 0x00000080){
            return (mem[novoEndereco] | 0xffffff00);
        }
        /* Se o byte for positivo */
        return (mem[novoEndereco] & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[1] >= 0x00008000){
            return ((mem[novoEndereco] >> 8) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[2] >= 0x00800000){
            return ((mem[novoEndereco] >> 16) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[3] >= 0x80000000){
            return ((mem[novoEndereco] >> 24) | 0xffffff00);
        }
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }
}

/* Lê meia palavra, 16 bits - retorna inteiro sem sinal */
int32_t lhu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        return (mem[novoEndereco] & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }
}

/* Lê um byte - retorna inteiro sem sinal */
int32_t lbu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        return (mem[novoEndereco] & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }
}
/******************************************************************************/

/* Escrita */
/* Escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
void sw(uint32_t endereco, int16_t deslocamento, int32_t dado){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("sw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4)\n");
        return;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Armazena o valor do dado no endereco */
    mem[(endereco + deslocamento)/4] = dado;
}

/* Escreve meia palavra, 16 bits - endereços múltiplos de 2 */
void sh(uint32_t endereco, int16_t deslocamento, int16_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("sh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2)\n");
        return;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        mem[novoEndereco] = (dado & 0x0000ffff) | (mem[novoEndereco] & 0xffff0000);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* 16 bits = 2 bytes */
        mem[novoEndereco] = ((dado & 0x0000ffff) << 16) | (mem[novoEndereco] & 0x0000ffff);
    }
}

/* Escreve um byte na memória */
void sb(uint32_t endereco, int16_t deslocamento, int8_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco;

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        mem[novoEndereco] = (dado & 0x000000ff) | (mem[novoEndereco] & 0xffffff00);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        mem[novoEndereco] = ((dado & 0x000000ff) << 8) | (mem[novoEndereco] & 0xffff00ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        mem[novoEndereco] = ((dado & 0x000000ff) << 16) | (mem[novoEndereco] & 0xff00ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        mem[novoEndereco] = ((dado & 0x000000ff) << 24) | (mem[novoEndereco] & 0x00ffffff);
    }
}

/******************************************************************************/
/* Menu */
/* Menu de interação com o usuário */
void menu (){
    int escolha = 0;
    uint32_t endereco = 0;

    do{
        printf("\n\n/**************SIMULADOR ASSEMBLER MIPS**************/\n\n");
        printf("(1) - Memory\n");
        printf("(2) - Load Word\n");
        printf("(3) - Load Halfword\n");
        printf("(4) - Load Halfword Unsigned\n");
        printf("(5) - Load Byte\n");
        printf("(6) - Load Byte Unsigned\n");
        printf("(7) - Store Word\n");
        printf("(8) - Store Halfword\n");
        printf("(9) - Store Byte\n");
        printf("(0) - Exit\n");
        printf("------------------------------------------------------\n");

        printf("Digite um valor correspondente a um opcao no menu: ");
        scanf("%d", &escolha);

        /* Memory */
        if(escolha == 1){
            printf("\n");

            /* Teste de insercao na memoria */
            for(endereco = 0; endereco < MEM_SIZE; endereco++){
                if(mem[endereco] != 0){
                    printf("Address [0x%.8x] = 0x%.8x\n", endereco*4, mem[endereco]);
                }
            }
        }

        /* Load Word */
        else if(escolha == 2){
            printf("\n");
            printf("lw(endereco, deslocamento) - Lê uma palavra (4 bytes)\n");

            uint32_t endereco;
            int16_t deslocamento;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nlw(%d,%d) = ", endereco, deslocamento);
            printf("0x%.8x", lw(endereco, deslocamento));
        }

        /* Load Halfword */
        else if(escolha == 3){
          printf("\n");
          printf("lh(endereco, deslocamento) - Lê uma meia-palavra (2 bytes)\n");

          uint32_t endereco;
          int16_t deslocamento;

          printf("\nDigite o endereco em decimal: ");
          scanf("%" SCNd32, &endereco);

          printf("\nDigite o deslocamento em bytes: ");
          scanf("%" SCNd16, &deslocamento);

          printf("\nlh(%d,%d) = ", endereco, deslocamento);
          printf("0x%.8x", lh(endereco, deslocamento));
        }

        /* Load Halfword Unsigned */
        else if(escolha == 4){
            printf("\n");
            printf("lhu(endereco, deslocamento) - Lê uma meia-palavra sem sinal (2 bytes)\n");

            uint32_t endereco;
            int16_t deslocamento;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nlhu(%d,%d) = ", endereco, deslocamento);
            printf("0x%.8x", lhu(endereco, deslocamento));
        }

        /* Load Byte */
        else if(escolha == 5){
            printf("\n");
            printf("lb(endereco, deslocamento) - Lê um byte\n");

            uint32_t endereco;
            int16_t deslocamento;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nlb(%d,%d) = ", endereco, deslocamento);
            printf("0x%.8x", lb(endereco, deslocamento));
        }

        /* Load Byte Unsigned */
        else if(escolha == 6){
            printf("\n");
            printf("lbu(endereco, deslocamento) - Lê uma byte sem sinal\n");

            uint32_t endereco;
            int16_t deslocamento;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nlbu(%d,%d) = ", endereco, deslocamento);
            printf("0x%.8x", lbu(endereco, deslocamento));
        }

        /* Store Word */
        else if(escolha == 7){
            printf("\n");
            printf("sw(endereco, deslocamento, dado) - Escreve uma palavra (4 bytes)\n");

            uint32_t endereco;
            int16_t deslocamento;
            int32_t dado;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nDigite o dado a ser armazenado: ");
            scanf("%" SCNd32, &dado);

            printf("\nPalavra escrita = ", endereco, deslocamento, dado);
            sw(endereco, deslocamento, dado);
            printf("0x%.8x", lw(endereco, deslocamento));
        }

        /* Store Halfword */
        else if(escolha == 8){
            printf("\n");
            printf("sh(endereco, deslocamento, dado) - Escreve meia-palavra (2 bytes)\n");

            uint32_t endereco;
            int16_t deslocamento;
            int16_t dado;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nDigite o dado a ser armazenado: ");
            scanf("%" SCNd16, &dado);

            printf("\nHalfword escrita = ", endereco, deslocamento, dado);
            sh(endereco, deslocamento, dado);
            printf("0x%.8x", (0x0000ffff & lh(endereco, deslocamento)));
        }

        /* Store Byte */
        else if(escolha == 9){
            printf("\n");
            printf("sb(endereco, deslocamento, dado) - Escreve meia-palavra (2 bytes)\n");

            uint32_t endereco;
            int16_t deslocamento;
            int8_t dado;

            printf("\nDigite o endereco em decimal: ");
            scanf("%" SCNd32, &endereco);

            printf("\nDigite o deslocamento em bytes: ");
            scanf("%" SCNd16, &deslocamento);

            printf("\nDigite o dado a ser armazenado: ");
            scanf("%" SCNd8, &dado);

            printf("\nByte escrito = ", endereco, deslocamento, dado);
            sb(endereco, deslocamento, dado);
            printf("0x%.8x", (0x000000ff & lb(endereco, deslocamento)));
        }

    }while(escolha != 0);

}
