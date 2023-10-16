//includes
#include "converte.h"

//main function 
int main(void){
//variables
  FILE *utfFile;
  FILE *varintFile;
  FILE *outputVarintV1;
  FILE *outputUtf8V1;
  FILE *outputVarintV2;
  FILE *outputUtf8V2;
  //execution
  
  //------------------------------------teste1-------------------------------------------------
  utfFile = abreArq("utf8_peq.txt","r");
  varintFile = abreArq("var_peq","rb");
  outputVarintV1 = abreArq("U->V(teste1)","wb");
  outputUtf8V1 = abreArq("V->U(teste1).txt","w");

    if (utfFile == NULL || varintFile == NULL ) {
        fprintf(stderr,"Erro ao abrir os arquivos do teste 1\n");
        return 1;
    }

    // Converta de UTF-8 para varint
    if (utf2varint(utfFile, outputVarintV1) == -1) {
        return 1;
    }


    // Converta de varint para UTF-8
    if (varint2utf(varintFile, outputUtf8V1) == -1) {
        return 1;
    }

    fclose(utfFile);
    fclose(varintFile);
    fclose(outputVarintV1);
    fclose(outputUtf8V1);
//----------------------------------teste2------------------------------------------------------
    utfFile = abreArq("utf8_demo.txt","r");
    varintFile = abreArq("var_demo","rb");
    outputVarintV2 = abreArq("U->V(teste2)","wb");
    outputUtf8V2 = abreArq("V->U(teste2).txt","w");

    if (utfFile == NULL || varintFile == NULL ) {
        fprintf(stderr,"Erro ao abrir os arquivos do teste 2\n");
        return 1;
    }

    // Converta de UTF-8 para varint
    if (utf2varint(utfFile, outputVarintV2) == -1) {
        return 1;
    }


    // Converta de varint para UTF-8
    if (varint2utf(varintFile, outputUtf8V2) == -1) {
        return 1;
    }

    fclose(utfFile);
    fclose(varintFile);
    fclose(outputVarintV2);
    fclose(outputUtf8V2);
    return 0;
}