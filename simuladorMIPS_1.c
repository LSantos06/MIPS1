#include "simuladorMIPS_1_funcoes.c"

int main(){
    FILE *arquivoData;
    FILE *arquivoText;

    uint32_t endereco = 0;

    /* Inicializando a memoria com 0 */
    for(endereco = 0; endereco < MEM_SIZE; endereco++){
        mem[endereco] = 0;
    }

    /* Abrindo o arquivo data.bin */
    arquivoData = fopen("data.bin", "rb");
    if(arquivoData == NULL){
        perror("Erro ao abrir arquivo data.bin");
        exit(-1);
    }

    /* Abrindo o arquivo text.bin */
    arquivoText = fopen("text.bin", "rb");
    if(arquivoText == NULL){
        perror("Erro ao abrir arquivo text.bin");
        exit(-1);
    }

    /* 0x20082000 => 0020 0820 => 2000 2008 => 0x20082000 */

    /* Carrega o arquivo data.bin na memoria */
    loadData(arquivoData);

    /* Carrega o arquivo text.bin na memoria */
    loadText(arquivoText);

    menu();

    fclose(arquivoData);
    fclose(arquivoText);

    return 0;
}
