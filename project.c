#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PATIENTS 50
#define LONGUEUR_MAX_DU_NOM 50
#define LONGUEUR_MAX_D_ADRESSE 100
#define LONGUEUR_MAX_D_HISTORIQUE 200

// Structure responsable de repr�senter un patient
typedef struct {
    int id;
    char nom[LONGUEUR_MAX_DU_NOM];
    char adresse[LONGUEUR_MAX_D_ADRESSE];
    int age;
    char sexe;
    char Description_Maladie[LONGUEUR_MAX_D_HISTORIQUE];
} Patient;

// Structure responsable de cr�ation de dossier patient
typedef struct {
    int id;
    int patientId;
    char nom_patient[LONGUEUR_MAX_DU_NOM];
    char Date_Creation[20]; // Format YYYY-MM-DD
    char Historique_Medical[LONGUEUR_MAX_D_HISTORIQUE];
} PatientRecord;

int dernierIdPatient = 0; // Variable globale pour suivre le dernier ID de patient attribu�

// Fonction pour ajouter un nouveau patient
void ajouterNouveauPatient(Patient patients[], int *nombrePatients) {
    if (*nombrePatients >= MAX_PATIENTS) {
        printf("\033[0;31m");
        printf("\n\t\t\t\t\t\t\t :( Capacite maximale de patients atteinte !\n");
        printf("\033[0m");
        return;
    }
    int i = 0;
    Patient nouveauPatient;
    nouveauPatient.id = ++dernierIdPatient; // Attribuer automatiquement l'ID du patient

    printf("\t\t\t\t\t\tEntrez le nom du patient : ");
    scanf(" %[^\n]s", nouveauPatient.nom);

    printf("\t\t\t\t\t\tEntrez l'adresse du patient : ");
    scanf(" %[^\n]s", nouveauPatient.adresse);

    do
    {
        printf("\t\t\t\t\t\tEntrez l'age du patient (entre 1 et 150 ans) : ");
        scanf("%d", &nouveauPatient.age);
        // V�rification de l'�ge pour s'assurer qu'il est dans la plage sp�cifi�e
        if (nouveauPatient.age < 1 || nouveauPatient.age > 150) {
            printf("\033[0;31m");
            printf("\n\t\t\t\t\t\t\t :( L'age doit etre compris entre 1 et 150 ans, reessayer !\n\n");
            printf("\033[0m");
        }
    } while (nouveauPatient.age < 1 || nouveauPatient.age > 150); // R�p�ter la saisie si l'�ge n'est pas valide

    do
    {
        printf("\t\t\t\t\t\tEntrez le sexe du patient (M/F) : ");
        scanf(" %c", &nouveauPatient.sexe);
        // V�rification du sexe pour s'assurer qu'il est 'M' ou 'F'
        if (toupper(nouveauPatient.sexe) != 'M' && toupper(nouveauPatient.sexe) != 'F') {
            printf("\033[0;31m");
            printf("\n\t\t\t\t\t\t\t :( Le sexe doit etre 'M' ou 'F',reessayer!\n\n");
            printf("\033[0m");
        }
    } while (toupper(nouveauPatient.sexe) != 'M' && toupper(nouveauPatient.sexe) != 'F'); // R�p�ter la saisie si le sexe n'est pas valide

    printf("\t\t\t\t\t\tEntrez la description de la maladie du patient : ");
    scanf(" %[^\n]s", nouveauPatient.Description_Maladie);

    patients[*nombrePatients] = nouveauPatient;
    (*nombrePatients)++;
    printf("\033[0;32m");
    printf("\n\t\t\t\t\t\t\t :) Patient ajoute avec succes avec l'ID : %d\n", nouveauPatient.id);
    printf("\033[0m");
}

// Fonction responsable de cr�ation de dossier patient
void creerDossierPatient(Patient patients[], int nombrePatients, PatientRecord dossiers[], int *nombreDossiers) {
    int idPatient;
    printf("\t\t\t\t\t\tEntrez l'ID du patient pour creer un dossier : ");
    scanf("%d", &idPatient);

    // Trouver le patient par ID
    int trouve = 0;
    for (int i = 0; i < nombrePatients; i++) {
        if (patients[i].id == idPatient) {
            PatientRecord nouveauDossier;
            nouveauDossier.id = *nombreDossiers + 1; // Attribuer automatiquement un ID de dossier unique
            nouveauDossier.patientId = patients[i].id;
            strcpy(nouveauDossier.nom_patient, patients[i].nom);

            // Obtenir la date actuelle pour la date de creation
            time_t maintenant = time(NULL);
            strftime(nouveauDossier.Date_Creation, sizeof(nouveauDossier.Date_Creation), "%Y-%m-%d", localtime(&maintenant));

            // Initialiser l'historique medical
            strcpy(nouveauDossier.Historique_Medical, patients[i].Description_Maladie);

            dossiers[*nombreDossiers] = nouveauDossier;
            (*nombreDossiers)++;
            printf("\033[0;32m");
            printf("\n\t\t\t\t\t\t\t :) Dossier patient cree avec succes pour l'ID du patient : %d\n", idPatient);
            printf("\033[0m");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("\033[0;31m");
        printf("\n\t\t\t\t\t\t\t :( Patient non trouve. Impossible de creer un dossier !\n");
        printf("\033[0m");
    }
}

// Fonction pour afficher tous les dossiers patients
void afficherDossiersPatients(PatientRecord dossiers[], int nombreDossiers) {
    if (nombreDossiers == 0)
    {
        printf("\033[0;31m");
        printf("\n\t\t\t\t\t\t\t :( Aucun dossier patient trouve !\n");
        printf("\033[0m");
        return;
    }
    printf("\033[1;35m");
    printf("\n\t\t\t\t\t\t\t\t      * Liste des dossiers patients : * ");
    for (int i = 0; i < nombreDossiers; i++) {
        printf("\n\t\t\t\t\t\t\t\t <=============================================>\n");
        printf("\t\t\t\t\t\t\t\t||      ID du dossier : %d\n", dossiers[i].id);
        printf("\t\t\t\t\t\t\t\t||      ID du patient : %d\n", dossiers[i].patientId);
        printf("\t\t\t\t\t\t\t\t||      Nom du patient : %s\n", dossiers[i].nom_patient);
        printf("\t\t\t\t\t\t\t\t||      Date de creation : %s\n", dossiers[i].Date_Creation);
        printf("\t\t\t\t\t\t\t\t||      Historique medical : %s\n", dossiers[i].Historique_Medical);
        printf("\t\t\t\t\t\t\t\t <=============================================>\n");
    }
    printf("\033[0m");
}

// Fonction pour supprimer un dossier patient
void supprimerDossierPatient(PatientRecord dossiers[], int *nombreDossiers) {
    int idDossier;
    printf("\t\t\t\t\t\tEntrez l'ID du dossier patient a supprimer : ");
    scanf("%d", &idDossier);

    // Recherche du dossier par son ID
    int trouve = 0;
    for (int i = 0; i < *nombreDossiers; i++) {
        if (dossiers[i].id == idDossier) {
            // D�placement des dossiers suivants pour combler le vide
            for (int j = i; j < *nombreDossiers - 1; j++) {
                dossiers[j] = dossiers[j + 1];
            }
            (*nombreDossiers)--;
            trouve = 1;
            printf("\033[0;32m");
            printf("\n\t\t\t\t\t\t\t :) Dossier patient supprime avec succes.\n");
            printf("\033[0m");
            break;
        }
    }

    if (!trouve) {
        printf("\033[0;31m");
        printf("\n\t\t\t\t\t\t\t :( Dossier patient non trouve !\n");
        printf("\033[0m");
    }
}

// Fonction pour chercher et afficher un dossier patient par son nom
void chercherDossierPatientParNom(PatientRecord dossiers[], int nombreDossiers, const char *nomPatient) {
    int trouve = 0;
    for (int i = 0; i < nombreDossiers; i++) {
        if (strcmp(dossiers[i].nom_patient, nomPatient) == 0) {
            printf("\033[1;34m");
            printf("\n\t\t\t\t\t\t\t\t      * Le dossier de ' %s ' : * ", dossiers[i].nom_patient);
            printf("\n\t\t\t\t\t\t\t\t <=============================================>\n");
            printf("\t\t\t\t\t\t\t\t||      ID du dossier : %d\n", dossiers[i].id);
            printf("\t\t\t\t\t\t\t\t||      ID du patient : %d\n", dossiers[i].patientId);
            printf("\t\t\t\t\t\t\t\t||      Nom du patient : %s\n", dossiers[i].nom_patient);
            printf("\t\t\t\t\t\t\t\t||      Date de creation : %s\n", dossiers[i].Date_Creation);
            printf("\t\t\t\t\t\t\t\t||      Historique medical : %s\n", dossiers[i].Historique_Medical);
            printf("\t\t\t\t\t\t\t\t <=============================================>\n");
            printf("\033[0m");
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("\033[0;31m");
        printf("\n\t\t\t\t\t\t\t :( Dossier patient non trouve !\n");
        printf("\033[0m");
    }
}

// Fonction d'affichage du menu principal
void afficherMenu() {
    printf("\n");
    printf("\n");
    printf("\033[1;33m"); // Set text color to yellow
    printf("\t\t\t\t\t\t1. Ajouter un nouveau patient ;\n");
    printf("\t\t\t\t\t\t2. Creer un dossier patient ;\n");
    printf("\t\t\t\t\t\t3. Chercher et afficher un dossier patient par son nom ;\n");
    printf("\t\t\t\t\t\t4. Afficher tous les dossiers patients ;\n");
    printf("\t\t\t\t\t\t5. Supprimer un dossier patient ;\n");
    printf("\t\t\t\t\t\t6. Quitter ;\n");
    printf("\033[0m"); // Reset text color to default
    printf("\033[1;36m"); // Set text color to cyan
    printf("\t\t\t\t\t\t======================================================================\n");
    printf("\033[0m"); // Reset text color to default
    printf("\t\t\t\t\t\t * Entrez votre choix : ");
}

int main() {
    int run;
    Patient patients[MAX_PATIENTS];
    PatientRecord dossiersPatients[MAX_PATIENTS];
    int nombrePatients = 0;
    int nombreDossiers = 0;
    int choix;

    printf("this project is created by : SOUHAIL RABII, WALID HAITI, OTHMANE KHALFAOUI, press ''1'' to run the project : \n");
    scanf("%d", &run);
    if (run == 1) {
        printf("\n");
        printf("\033[1;31m"); // Set text color to red
        printf("\t\t\t\t\t\t\t  _   _      _ _         __        __         _     _ _ \n");
        printf("\t\t\t\t\t\t\t | | | | ___| | | ___    \\ \\      / /__  _ __| | __| | |\n");
        printf("\t\t\t\t\t\t\t | |_| |/ _ \\ | |/ _ \\    \\ \\ /\\ / / _ \\| '__| |/ _` | |\n");
        printf("\t\t\t\t\t\t\t |  _  |  __/ | | (_) |    \\ V  V / (_) | |  | | (_| |_|\n");
        printf("\t\t\t\t\t\t\t |_| |_|\\___|_|_|\\___( )    \\_/\\_/ \\___/|_|  |_|\\__,_(_)\n");
        printf("\t\t\t\t\t\t\t                     |/                                 \n\n");
        printf("\033[0m"); // Reset text color to default
        printf("\033[1;36m"); // Set text color to cyan
        printf("\t\t\t\t\t\t======================================================================\n");
        printf("\t\t\t\t\t\t      |||||||||||  Bienvenue au Gestion Hospitaliere  ||||||||||\n");
        printf("\t\t\t\t\t\t======================================================================\n");

        do {
            afficherMenu();
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    ajouterNouveauPatient(patients, &nombrePatients);
                    break;
                case 2:
                    creerDossierPatient(patients, nombrePatients, dossiersPatients, &nombreDossiers);
                    break;
                case 3: {
                    char nomPatient[LONGUEUR_MAX_DU_NOM];
                    printf("\t\t\t\t\t\tEntrez le nom du patient : ");
                    scanf(" %[^\n]s", nomPatient);
                    chercherDossierPatientParNom(dossiersPatients, nombreDossiers, nomPatient);
                    break;
                }
                case 4:
                    afficherDossiersPatients(dossiersPatients, nombreDossiers);
                    break;
                case 5:
                    supprimerDossierPatient(dossiersPatients, &nombreDossiers);
                    break;
                case 6:
                    printf("\033[0;32m");
                    printf("\n\n\t\t\t\t\t\t :) Programme termine !!\n\n\n");
                    printf("\033[0m");
                    printf("\033[0;31m");
                    printf("\t\t\t\t\t\t\t  _______ _                 _     __     __\n");
                    printf("\033[0;31m");
                    printf("\t\t\t\t\t\t\t |__   __| |               | |    \\ \\   / /\n");
                    printf("\033[0;36m");
                    printf("\t\t\t\t\t\t\t    | |  | |__   __ _ _ __ | | __  \\ \\_/ /__  _   _\n");
                    printf("\033[0;34m");
                    printf("\t\t\t\t\t\t\t    | |  | '_ \\ / _` | '_ \\| |/ /   \\   / _ \\| | | |\n");
                    printf("\033[0;33m");
                    printf("\t\t\t\t\t\t\t    | |  | | | | (_| | | | |   <     | | (_) | |_| | \n");
                    printf("\033[0;35m");
                    printf("\t\t\t\t\t\t\t    |_|  |_| |_|\\__,_|_| |_|_|\\_\\    |_|\\___/ \\__,_|\n");
                    printf("\t\t\t\t\t\t\t                                                           \n\n");
                    break;
                default:
                    printf("\033[0;31m");
                    printf("\n\t\t\t\t\t\t\t :( Choix invalide. Veuillez reessayer !\n");
                    printf("\033[0m");
            }

        } while (choix != 6);
    } else {
        return 0;
    }

    return 0;
}
