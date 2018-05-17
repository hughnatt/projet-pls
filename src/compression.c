#include "analyse.h"
#include "huffman.h"
#include "codage.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>

static void displaytab256(uint8_t tab[256]){
    for (int k = 0; k < 256 ; k++){
        //if ( tab[k] != 0){
            printf("%d | ",k);
            for (int i = 0; i < 8; i++){
                printf("%d", !!((tab[k] << i) & 0x80));
            }
            printf(" \n");
        //}
    }
    printf("\n");
}




int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Syntaxe : ./compression <filename>\n");
        return -1;
    }

    uint64_t freq_tab[256];
    uint8_t prof_tab[256];
    uint64_t code_tab[256];

    //printf("========= TABLEAU FREQUENCES ========\n");
    frequences(argv[1],freq_tab);
    //ecriture_tableau_freq(freq_tab);


    phtree_t hufftree = creer_htree(freq_tab);
    profondeur(hufftree, prof_tab);
    afficher_arbre(hufftree,1);    
    displaytab256(prof_tab);
    detruire_htree(hufftree);


    phtree_t huffcan = arbre_canonique(prof_tab);
    afficher_arbre(huffcan,1);


    correspondance(huffcan,code_tab);
    //printf("TABLEAU DE CODES\n");
    //displaytab256(code_tab);

    transcodage(argv[1],"fencode.txt",code_tab,prof_tab);


    return 0;
}

