#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <netax25/procutils.h>

// --- Definitions and Constants ---

#define PROC_AX25_FILE "/proc/net/ax25"
#define LINE_MAX_LEN 2048
#define MAX_FIELDS 32

int has_header = 0; 

// Assurez-vous que cette structure est bien définie dans netax25/procutils.h
typedef struct proc_ax25 proc_ax25_t;

// Fonction pour libérer la mémoire de la liste
void free_ax25_list(proc_ax25_t *head) {
    proc_ax25_t *tmp;
    while (head != NULL) {
        tmp = head; head = head->next; free(tmp);
    }
}

// --------------------------------------------------
// --- NOUVELLE FONCTION : INVERSION DE LA LISTE ---
// --------------------------------------------------

proc_ax25_t *reverse_ax25_list(proc_ax25_t *head) {
    proc_ax25_t *prev = NULL;
    proc_ax25_t *current = head;
    proc_ax25_t *next = NULL;

    while (current != NULL) {
        next = current->next; // 1. Sauvegarder le prochain élément
        current->next = prev; // 2. Pointer l'élément courant vers l'élément précédent
        prev = current;       // 3. Déplacer 'prev' à l'élément courant
        current = next;       // 4. Déplacer 'current' à l'élément suivant sauvegardé
    }
    // Le nouvel 'head' est l'ancien 'prev' (qui pointe vers la dernière connexion lue)
    return prev;
}

// --------------------------------------------------
// --- Test application for new procutils library ---
// --------------------------------------------------

int main() {

    const int SEPARATOR_WIDTH = 165;
    
    void draw_separator(char character) {
        for (int i = 0; i < SEPARATOR_WIDTH; i++) {
            putchar(character);
        }
        putchar('\n');
    }
    
    printf("Start of AX.25 connections sockets reading.\n");
    draw_separator('=');
    
    // 1. Lire les connexions (elles sont dans l'ordre du fichier /proc)
    proc_ax25_t *connections = read_proc_ax25();
    
    if (connections == NULL) {
        printf("No active AX.25 connection found.\n");
        draw_separator('='); 
        return EXIT_SUCCESS;
    }

    // 2. INVERSER LA LISTE pour afficher les dernières connexions d'abord
//    connections = reverse_ax25_list(connections); 
    
    printf("Format /proc/net/ax25: %s\n", has_header ? "NEW (with Header)" : "OLD (without Header)");
    draw_separator('-');
    
    printf("%-8s %-10s %-10s %-10s %-10s %-3s %-3s %-3s %-3s %-4s %-4s %-4s %-4s %-5s %-5s %-5s %-5s %-4s %-5s %-4s %-4s %-5s %-9s %-6s %-10s\n", 
           "MAGIC", "DEV", "SRC", "DEST", "DIGI1", "ND", "ST", "VS", "VR", "VA", 
           "T1T", "T1", "T2T", "T2", "T3T", "T3", 
           "IDLT", "IDLE", "N2C", "N2", "RTT", "WIN", "PACL", "SQ/RQ", "INODE");
    draw_separator('-');

    proc_ax25_t *curr = connections;
    while (curr != NULL) {
        printf("%08lx %-10s %-10s %-10s %-10s %-3d %-3d %-3d %-3d %-4d %-4lu %-4lu %-4lu %-4lu %-5lu %-5lu %-5lu %-5lu %-4d %-4d %-6lu %-4d %-5d %-4d %-4d %-10lu\n",
                curr->magic, 
                curr->dev, 
                curr->src_addr, 
                curr->dest_addr, 
                curr->digi_addr[0], 
                curr->ndigi,
                (int)curr->st, 
                curr->vs,
                curr->vr,
                curr->va,
                curr->t1timer, curr->t1,
                curr->t2timer, curr->t2,
                curr->t3timer, curr->t3,
                curr->idletimer, curr->idle,
                (int)curr->n2count, (int)curr->n2,
                curr->rtt,           
                (int)curr->window,    
                curr->paclen,          
                curr->sndq,            
                curr->rcvq,            
                curr->inode           
        ); 
        curr = curr->next;
    }

    draw_separator('=');
    free_ax25_list(connections);
    return EXIT_SUCCESS;
}
