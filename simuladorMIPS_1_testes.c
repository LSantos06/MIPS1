#include "simuladorMIPS_1_funcoes.c"

int main(){
    FILE *arquivoData;
    FILE *arquivoText;

    uint32_t endereco = 0;
    int teste;

    /* Inicializando a memoria com 0 */
    for(endereco = 0; endereco < MEM_SIZE; endereco++){
        mem[endereco] = 0;
    }

    printf("\n\n/******************TESTES******************/\n\n");
    /* Abrindo o arquivo data.bin */
    arquivoData = fopen("data.bin", "rb");
    if(arquivoData == NULL){
        perror("Erro ao abrir arquivo data.bin");
        exit(-1);
    }

    /* Teste de leitura */
    printf("/******************Teste de leitura do arquivo data.bin******************/\n");
    while(!feof(arquivoData)){
        fread(&teste, sizeof(int32_t), 1, arquivoData);
        if(teste != 0){
            printf("0x%.8x\n", teste);
        }
    }
    getchar();

    /* Abrindo o arquivo text.bin */
    arquivoText = fopen("text.bin", "rb");
    if(arquivoText == NULL){
        perror("Erro ao abrir arquivo text.bin");
        exit(-1);
    }

    /* Teste de leitura */
    printf("/******************Teste de leitura do arquivo text.bin******************/\n");
    while(!feof(arquivoText)){
        fread(&teste, sizeof(int32_t), 1, arquivoText);
        if(teste != 0){
            printf("0x%.8x\n", teste);
        }
    }
    getchar();

    /* 0x20082000 => 0020 0820 => 2000 2008 => 0x20082000 */

    /* Carrega o arquivo data.bin na memoria */
    rewind(arquivoData);
    loadData(arquivoData);

    /* Carrega o arquivo text.bin na memoria */
    rewind(arquivoText);
    loadText(arquivoText);

    /* Teste de insercao na memoria */
    printf("/******************Teste de insercao na memoria******************/\n");
    for(endereco = 0; endereco < MEM_SIZE; endereco++){
        if(mem[endereco] != 0){
            printf("Address [0x%.8x] = 0x%.8x\n", endereco*4, mem[endereco]);
        }
    }
    getchar();

    /* Testes Críticos */
    /* Load Word */
    printf("\n/******************Teste Load Word******************/\n");
    /* Endereco ou Deslocamento invalido */
    printf("lw(0,1), Esperado = erro; Resultado = 0x%.8x\n", lw(0,1));
    /* Caso base */
    printf("lw(0,0), Esperado = valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    /* Deslocamento de uma palavra */
    printf("lw(0,4), Esperado = valor do address [0x00000004]; Resultado = 0x%.8x\n", lw(0,4));
    getchar();

    /* Load Halfword */
    printf("\n/******************Teste Load Halfword******************/\n");
    /* Endereco ou Deslocamento invalido */
    printf("lh(0,1), Esperado = erro; Resultado = 0x%.8x\n", lh(0,1));
    /* Casos bases */
    printf("lh(0,0), Esperado = 2 lsbytes do address [0x00000000]; Resultado = 0x%.8x\n", lh(0,0));
    printf("lh(0,2), Esperado = 2 msbytes do address [0x00000000]; Resultado = 0x%.8x\n", lh(0,2));
    /* Deslocamento de meia-palavra */
    printf("lh(0,4), Esperado = 2 lsbytes do address [0x00000004]; Resultado = 0x%.8x\n", lh(0,4));
    /* Conteudos negativos */
    printf("lh(56,0), Esperado = 2 lsbytes do address [0x00000038], em complemento de 2; Resultado = 0x%.8x\n", lh(56,0));
    getchar();

    /* Load Halfword Unsigned*/
    printf("\n/******************Teste Load Halfword Unsigned******************/\n");
    /* Endereco ou Deslocamento invalido */
    printf("lhu(0,1), Esperado = erro; Resultado = 0x%.8x\n", lhu(0,1));
    /* Casos bases */
    printf("lhu(0,0), Esperado = 2 lsbytes do address [0x00000000]; Resultado = 0x%.8x\n", lhu(0,0));
    printf("lhu(0,2), Esperado = 2 msbytes do address [0x00000000]; Resultado = 0x%.8x\n", lhu(0,2));
    /* Deslocamento de meia-palavra */
    printf("lhu(0,4), Esperado = 2 lsbytes do address [0x00000004]; Resultado = 0x%.8x\n", lhu(0,4));
    /* Conteudos negativos */
    printf("lhu(56,0), Esperado = 2 lsbytes do address [0x00000038]; Resultado = 0x%.8x\n", lhu(56,0));

    getchar();

    /* Load Byte */
    printf("\n/******************Teste Load Byte******************/\n");
    /* Casos bases */
    printf("lb(0,0), Esperado = lsbyte do address [0x00000000]; Resultado = 0x%.8x\n", lb(0,0));
    printf("lb(0,1), Esperado = segundo lsbyte do address [0x00000000]; Resultado = 0x%.8x\n", lb(0,1));
    printf("lb(0,2), Esperado = segundo msbyte do address [0x00000000]; Resultado = 0x%.8x\n", lb(0,2));
    printf("lb(0,3), Esperado = msbyte do address [0x00000000]; Resultado = 0x%.8x\n", lb(0,3));
    /* Deslocamento de meia-palavra */
    printf("lb(0,4), Esperado = lsbyte do address [0x00000004]; Resultado = 0x%.8x\n", lb(0,4));
    /* Conteudos negativos */
    printf("lb(56,0), Esperado = 2 lsbytes do address [0x00000038], em complemento de 2; Resultado = 0x%.8x\n", lb(56,0));
    getchar();

    /* Load Byte Unsigned*/
    printf("\n/******************Teste Load Byte Unsigned******************/\n");
    /* Casos bases */
    printf("lbu(0,0), Esperado = lsbyte do address [0x00000000]; Resultado = 0x%.8x\n", lbu(0,0));
    printf("lbu(0,1), Esperado = segundo lsbyte do address [0x00000000]; Resultado = 0x%.8x\n", lbu(0,1));
    printf("lbu(0,2), Esperado = segundo msbyte do address [0x00000000]; Resultado = 0x%.8x\n", lbu(0,2));
    printf("lbu(0,3), Esperado = msbyte do address [0x00000000]; Resultado = 0x%.8x\n", lbu(0,3));
    /* Deslocamento de meia-palavra */
    printf("lbu(0,4), Esperado = lsbyte do address [0x00000004]; Resultado = 0x%.8x\n", lbu(0,4));
    /* Conteudos negativos */
    printf("lbu(56,0), Esperado = lsbyte do address [0x00000038]; Resultado = 0x%.8x\n", lbu(56,0));
    getchar();

    /* Store Word */
    printf("\n/******************Teste Store Word******************/\n");
    /* Endereco ou Deslocamento invalido */
    sw(0,1,0);
    printf("sw(0,1,0), Esperado = erro; Resultado = 0x%.8x\n", lw(0,0));
    /* Caso base */
    sw(0,0,0);
    printf("sw(0,0,0), Esperado = 0x00000000 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    /* Deslocamento de uma palavra */
    sw(0,4,0);
    printf("sw(0,4,0), Esperado = 0x00000000 no valor do address [0x00000004]; Resultado = 0x%.8x\n", lw(0,4));
    getchar();

    /* Store Halfword */
    printf("\n/******************Teste Store Halfword******************/\n");
    /* Endereco ou Deslocamento invalido */
    sh(0,1,0);
    printf("sh(0,1,0), Esperado = erro; Resultado = 0x%.8x\n", lh(0,1));
    /* Caso base */
    sh(0,0,-64);
    printf("sh(0,0,-64), Esperado = 0x0000ffc0 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    sh(0,2,-64);
    printf("sh(0,2,-64), Esperado = 0xffc0ffc0 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    /* Deslocamento de uma palavra */
    sh(0,4,-64);
    printf("sh(0,4,-64), Esperado = 0x0000ffc0 no valor do address [0x00000004]; Resultado = 0x%.8x\n", lw(0,4));
    getchar();

    /* Store Byte */
    printf("\n/******************Teste Store Byte******************/\n");
    /* Caso base */
    sb(0,0,0);
    printf("sh(0,0,-16), Esperado = 0xffc0ff00 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    sb(0,1,0);
    printf("sh(0,2,-16), Esperado = 0xffc00000 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    sb(0,2,0);
    printf("sh(0,2,-16), Esperado = 0xff000000 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    sb(0,3,0);
    printf("sh(0,2,-16), Esperado = 0x00000000 no valor do address [0x00000000]; Resultado = 0x%.8x\n", lw(0,0));
    /* Deslocamento de uma palavra */
    sb(0,4,0);
    printf("sh(0,4,-64), Esperado = 0x0000ff00 no valor do address [0x00000004]; Resultado = 0x%.8x\n", lw(0,4));
    getchar();

    fclose(arquivoData);
    fclose(arquivoText);

    return 0;
}
