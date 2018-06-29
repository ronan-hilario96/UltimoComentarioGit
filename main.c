#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* concat(const char *s1, const char *s2);
void maisMemoria(char **cadeiaCaracteres);
char * leituraRapida(const char * caminho, const char * parametroDeBusca);


int main(const unsigned int argc, const char **argv)
{
    char *localGit = concat("", argv[1]);
    char *master = leituraRapida(concat(localGit, "HEAD"), "ref: %s");
    char *hash = leituraRapida(concat(localGit, master), "%s");

    FILE *file = fopen(concat(localGit, "logs/refs/heads/master"),"rb");
    char *linhaDepoisValidacao = calloc(1, sizeof(1));
    char *buffer = calloc(1, 41);
    char c[2] = "\0";
    bool iniciaColeta = false;
    while ((c[0] = fgetc(file)) != EOF){
        if(iniciaColeta == true){
            if(linhaDepoisValidacao[strlen(linhaDepoisValidacao) - 2] != '\0')
                maisMemoria(&linhaDepoisValidacao);
            strcat(linhaDepoisValidacao, c);
            if(c[0] == '\n') break;
        } else {
            if (strcmp(buffer, hash) == 0) {
                iniciaColeta = true;
            } else {
                if(c[0] == ' ' || c[0] == '\n'){
                    free(buffer);
                    buffer = calloc(1, 41);
                    continue;
                }
                if (strlen(buffer) == 41) {
                    free(buffer);
                    buffer = calloc(1, 41);
                }
                strcat(buffer, c);
            }
        }
    }
    printf("%s\n", linhaDepoisValidacao);
    fclose(file);
    return 0;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
void maisMemoria(char **cadeiaCaracteres){
    int auxiliar = calloc(1, strlen(*cadeiaCaracteres));
    strcpy(auxiliar, *cadeiaCaracteres);
    *cadeiaCaracteres = calloc(1, 2 + strlen(*cadeiaCaracteres));
    strcpy(*cadeiaCaracteres, auxiliar);
    free(auxiliar);
}
char * leituraRapida(const char * caminho, const char * parametroDeBusca){
    FILE *file = fopen(caminho,"rb");
    char *ref = calloc(1, 200);
    fscanf(file, parametroDeBusca, ref);
    fclose(file);
    return ref;
}