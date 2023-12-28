#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int i, j;
int main_exit;
void menu();

struct date {
    int mois, jour, annee;
};


struct {
    char nom[60];
    int num_compte, age;
    char adresse[60];
    char nationalite[15];
    double telephone;
    char type_compte[10];
    float montant;
    struct date naissance;
    struct date depot;
    struct date retrait;
} ajouter, mettre_a_jour, verifier, supprimer, transaction;


float interet(float t, float montant, int taux)
{
    float SI;
    SI = (taux * t * montant) / 100.0;
    return (SI);
}


void attente(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}


void nouveau_compte()
{
    int choix;
    FILE *fichier;

    fichier = fopen("enregistrement.dat", "a+");
    numero_compte:
    system("cls");
    printf("\t\t\t\xB2\xB2\xB2\ AJOUTER UN ENREGISTREMENT  \xB2\xB2\xB2\xB2");
    printf("\n\n\nEntrez la date d'aujourd'hui (mm/jj/aaaa) :");
    scanf("%d/%d/%d", &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee);
    printf("\nEntrez le numero de compte :");
    scanf("%d", &verifier.num_compte);
    while (fscanf(fichier, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
    {
        if (verifier.num_compte == ajouter.num_compte)
        {
            printf("Numero de compte deja utilise !");

            goto numero_compte;
        }
    }
    ajouter.num_compte = verifier.num_compte;
    printf("\nEntrez le nom :");
    scanf("%s", ajouter.nom);
    printf("\nEntrez la date de naissance (mm/jj/aaaa) :");
    scanf("%d/%d/%d", &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee);
    printf("\nEntrez l'age :");
    scanf("%d", &ajouter.age);
    printf("\nEntrez l'adresse :");
    scanf("%s", ajouter.adresse);
    printf("\nEntrez le numero de carte d'identite :");
    scanf("%s", ajouter.nationalite);
    printf("\nEntrez le numero de telephone : ");
    scanf("%lf", &ajouter.telephone);
    printf("\nEntrez le montant à deposer : $");
    scanf("%f", &ajouter.montant);
    printf("\nType de compte :\n\t#Epargne\n\t#Courant\n\t#Fixe1 (pour 1 an)\n\t#Fixe2 (pour 2 ans)\n\t#Fixe3 (pour 3 ans)\n\n\tEntrez votre choix :");
    scanf("%s", ajouter.type_compte);

    fprintf(fichier, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);

    fclose(fichier);
    printf("\nCompte cree avec succes !");
    ajout_invalide:
    printf("\n\n\n\t\tEntrez 1 pour aller au menu principal et 0 pour quitter :");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        fermer();
    else
    {
        printf("\nInvalide !\a");
        goto ajout_invalide;
    }
}


void afficher_liste()
{
    FILE *vue;
    vue = fopen("enregistrement.dat", "r");
    int test = 0;
    system("cls");
    printf("\nNUM. COMPTE\tNOM\t\t\tADRESSE\t\t\tTELEPHONE\n");

    while (fscanf(vue, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
    {
        printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf", ajouter.num_compte, ajouter.nom, ajouter.adresse, ajouter.telephone);
        test++;
    }

    fclose(vue);
    if (test == 0)
    {
        system("cls");
        printf("\nAUCUN ENREGISTREMENT !!\n");
    }

    liste_invalide:
    printf("\n\nEntrez 1 pour aller au menu principal et 0 pour quitter :");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        fermer();
    else
    {
        printf("\nInvalide !\a");
        goto liste_invalide;
    }
}


void modifier(void)
{
    int choix, test = 0;
    FILE *ancien, *nouveau;
    ancien = fopen("enregistrement.dat", "r");
    nouveau = fopen("nouveau.dat", "w");

    printf("\nEntrez le numero de compte du client dont vous souhaitez modifier les informations :");
    scanf("%d", &mettre_a_jour.num_compte);
    while (fscanf(ancien, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
    {
        if (ajouter.num_compte == mettre_a_jour.num_compte)
        {
            test = 1;
            printf("\nQuelle information souhaitez-vous changer ?\n1. Adresse\n2. Téléphone\n\nEntrez votre choix (1 pour l'adresse et 2 pour le telephone) :");
            scanf("%d", &choix);
            system("cls");
            if (choix == 1)
            {
                printf("Entrez la nouvelle adresse :");
                scanf("%s", mettre_a_jour.adresse);
                fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, mettre_a_jour.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
                system("cls");
                printf("Changements enregistrés !");
            }
            else if (choix == 2)
            {
                printf("Entrez le nouveau numero de telephone :");
                scanf("%lf", &mettre_a_jour.telephone);
                fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, mettre_a_jour.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
                system("cls");
                printf("Changements enregistres !");
            }
        }
        else
            fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
    }
    fclose(ancien);
    fclose(nouveau);
    remove("enregistrement.dat");
    rename("nouveau.dat", "enregistrement.dat");

    if (test != 1)
    {
        system("cls");
        printf("\nEnregistrement non trouve !!\a\a\a");
        edit_invalide:
        printf("\nEntrez 0 pour reessayer, 1 pour retourner au menu principal et 2 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            fermer();
        else if (main_exit == 0)
            modifier();
        else
        {
            printf("\nInvalide !\a");
            goto edit_invalide;
        }
    }
    else
    {
        printf("\n\n\nEntrez 1 pour aller au menu principal et 0 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            fermer();
    }
}


void effectuer_transaction(void)
{
    int choix, test = 0;
    FILE *ancien, *nouveau;
    ancien = fopen("enregistrement.dat", "r");
    nouveau = fopen("nouveau.dat", "w");

    printf("Entrez le numero de compte du client :");
    scanf("%d", &transaction.num_compte);
    while (fscanf(ancien, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
    {
        if (ajouter.num_compte == transaction.num_compte)
        {
            test = 1;
            if (strcmpi(ajouter.type_compte, "fixe1") == 0 || strcmpi(ajouter.type_compte, "fixe2") == 0 || strcmpi(ajouter.type_compte, "fixe3") == 0)
            {
                printf("\a\a\a\n\nVOUS NE POUVEZ PAS DÉPOSER OU RETIRER DE L'ARGENT DANS DES COMPTES FIXES !!!!");

                system("cls");
                menu();
            }
            printf("\n\nQue voulez-vous faire ?\n1.Déposer\n2.Retirer?\n\nEntrez votre choix (1 pour déposer et 2 pour retirer) :");
            scanf("%d", &choix);
            if (choix == 1)
            {
                printf("Entrez le montant que vous voulez deposer : $");
                scanf("%f", &transaction.montant);
                ajouter.montant += transaction.montant;
                fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
                system("cls");
                printf("Dépôt effectue avec succes !");
            }
            else if (choix == 2)
            {
                printf("Entrez le montant que vous voulez retirer : $");
                scanf("%f", &transaction.montant);
                ajouter.montant -= transaction.montant;
                fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
                system("cls");
                printf("Retrait effectue avec succes !");
            }
        }
        else
        {
            fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
        }
    }
    fclose(ancien);
    fclose(nouveau);
    remove("enregistrement.dat");
    rename("nouveau.dat", "enregistrement.dat");

    if (test != 1)
    {
        printf("\n\nEnregistrement non trouve !!");
        transaction_invalide:
        printf("\n\n\nEntrez 0 pour reessayer, 1 pour retourner au menu principal et 2 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            effectuer_transaction();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            fermer();
        else
        {
            printf("\nInvalide !");
            goto transaction_invalide;
        }
    }
    else
    {
        printf("\nEnterz 1 pour aller au menu principal et 0 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            fermer();
    }
}


void effacer(void)
{
    FILE *ancien, *nouveau;
    int test = 0;
    ancien = fopen("enregistrement.dat", "r");
    nouveau = fopen("nouveau.dat", "w");
    printf("Entrez le numero de compte du client que vous souhaitez supprimer :");
    scanf("%d", &supprimer.num_compte);
    while (fscanf(ancien, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
    {
        if (ajouter.num_compte != supprimer.num_compte)
            fprintf(nouveau, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone, ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);
        else
        {
            test++;
            printf("\nEnregistrement supprime avec succes !\n");
        }
    }
    fclose(ancien);
    fclose(nouveau);
    remove("enregistrement.dat");
    rename("nouveau.dat", "enregistrement.dat");
    if (test == 0)
    {
        printf("\nEnregistrement non trouve!!\a\a\a");
        effacer_invalide:
        printf("\nEntrez 0 pour reessayer, 1 pour retourner au menu principal et 2 pour quitter:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            fermer();
        else if (main_exit == 0)
            effacer();
        else
        {
            printf("\nInvalide!\a");
            goto effacer_invalide;
        }
    }
    else
    {
        printf("\nEntrez 1 pour aller au menu principal et 0 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            fermer();
    }
}


void consulter(void)
{
    FILE *ptr;
    int test = 0, taux;
    int choix;
    float temps;
     float interet1;

    ptr = fopen("enregistrement.dat", "r");
    printf("Voulez-vous verifier par\n1. Numero de compte\n2. Nom\nEntrez votre choix :");
    scanf("%d", &choix);
    if (choix == 1)
    {
        printf("Entrez le numero de compte :");
        scanf("%d", &verifier.num_compte);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
        {
            if (ajouter.num_compte == verifier.num_compte)
            {
                system("cls");
                test = 1;

                printf("\nNumero de compte : %d\nNom : %s \nDate de naissance : %d/%d/%d \nÂge : %d \nAdresse : %s \nNumero de citoyennete : %s \nNumero de telephone : %.0lf \nType de compte : %s \nMontant depose : $%.2f \nDate de depot : %d/%d/%d\n\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone,
                       ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);

                if (strcmpi(ajouter.type_compte, "fixe1") == 0)
                {
                    temps = 1.0;
                    taux = 9;

                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $%.2f d'interets le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 1);
                }
                else if (strcmpi(ajouter.type_compte, "fixe2") == 0)
                {
                    temps = 2.0;
                    taux = 11;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérets le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 2);
                }
                else if (strcmpi(ajouter.type_compte, "fixe3") == 0)
                {
                    temps = 3.0;
                    taux = 13;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérets le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 3);
                }
                else if (strcmpi(ajouter.type_compte, "épargne") == 0)
                {
                    temps = (1.0 / 12.0);
                    taux = 8;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérêts le %d de chaque mois", interet1, ajouter.depot.jour);
                }
                else if (strcmpi(ajouter.type_compte, "courant") == 0)
                {
                    printf("\n\nVous ne recevrez aucun interet\a\a");
                }
            }
        }
    }
    else if (choix == 2)
    {
        printf("Entrez le nom :");
        scanf("%s", &verifier.nom);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d", &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee, &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte, &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF)
        {
            if (strcmpi(ajouter.nom, verifier.nom) == 0)
            {
                system("cls");
                test = 1;
                printf("\nNuméro de compte : %d\nNom : %s \nDate de naissance : %d/%d/%d \nÂge : %d \nAdresse : %s \nNuméro de citoyenneté : %s \nNuméro de téléphone : %.0lf \nType de compte : %s \nMontant déposé : $%.2f \nDate de dépôt : %d/%d/%d\n\n", ajouter.num_compte, ajouter.nom, ajouter.naissance.mois, ajouter.naissance.jour, ajouter.naissance.annee, ajouter.age, ajouter.adresse, ajouter.nationalite, ajouter.telephone,
                       ajouter.type_compte, ajouter.montant, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee);

                if (strcmpi(ajouter.type_compte, "fixe1") == 0)
                {
                    temps = 1.0;
                    taux = 9;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérêts le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 1);
                }
                else if (strcmpi(ajouter.type_compte, "fixe2") == 0)
                {
                    temps = 2.0;
                    taux = 11;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérêts le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 2);
                }
                else if (strcmpi(ajouter.type_compte, "fixe3") == 0)
                {
                    temps = 3.0;
                    taux = 13;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérêts le %d/%d/%d", interet1, ajouter.depot.mois, ajouter.depot.jour, ajouter.depot.annee + 3);
                }
                else if (strcmpi(ajouter.type_compte, "épargne") == 0)
                {
                    temps = (1.0 / 12.0);
                    taux = 8;
                    interet1 = interet(temps, ajouter.montant, taux);
                    printf("\n\nVous recevrez $.%.2f d'intérêts le %d de chaque mois", interet1, ajouter.depot.jour);
                }
                else if (strcmpi(ajouter.type_compte, "courant") == 0)
                {
                    printf("\n\nVous ne recevrez aucun intérêt\a\a");
                }
            }
        }
    }

    fclose(ptr);
    if (test != 1)
    {
        system("cls");
        printf("\nEnregistrement non trouvé!!\a\a\a");
        consulter_invalide:
        printf("\nEntrez 0 pour réessayer, 1 pour retourner au menu principal et 2 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            fermer();
        else if (main_exit == 0)
            consulter();
        else
        {
            system("cls");
            printf("\nInvalide!\a");
            goto consulter_invalide;
        }
    }
    else
    {
        printf("\nEntrez 1 pour aller au menu principal et 0 pour quitter :");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            fermer();
    }
}


void fermer(void)
{
    printf("\n\n\n\nCe mini-projet C a ete developpe par Mohamed Lahiani !");
}




void calculer_somme_soldes() {
    FILE *fichier;
    float somme_soldes = 0;

    fichier = fopen("enregistrement.dat", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return;
    }

    while (fscanf(fichier, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee,
                  &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte,
                  &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF) {

        if (ajouter.montant > 0) {
            somme_soldes += ajouter.montant;
        }
    }

    fclose(fichier);

    printf("La somme totale des soldes des comptes actifs est : $%.2f\n", somme_soldes);
}


void afficher_nombre_total_comptes() {
    FILE *fichier;
    int nombre_total_comptes = 0;

    fichier = fopen("enregistrement.dat", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return;
    }

    while (fscanf(fichier, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &ajouter.num_compte, ajouter.nom, &ajouter.naissance.mois, &ajouter.naissance.jour, &ajouter.naissance.annee,
                  &ajouter.age, ajouter.adresse, ajouter.nationalite, &ajouter.telephone, ajouter.type_compte,
                  &ajouter.montant, &ajouter.depot.mois, &ajouter.depot.jour, &ajouter.depot.annee) != EOF) {
        nombre_total_comptes++;
    }

    fclose(fichier);

    printf("Le nombre total de comptes clients enregistrés est : %d\n", nombre_total_comptes);
}



void menu() {
    int choix;

    do {
        printf("\n\n\t\t\t\t========== GESTION DE BANQUE ==========");
        printf("\n\n\t\t\t\t\t\t\t\t1. Nouveau compte");
        printf("\n\t\t\t\t\t\t\t\t2. Modifier compte");
        printf("\n\t\t\t\t\t\t\t\t3. Consulter compte");
        printf("\n\t\t\t\t\t\t\t\t4. Supprimer compte");
        printf("\n\t\t\t\t\t\t\t\t5. Liste de tous les comptes");
        printf("\n\t\t\t\t\t\t\t\t6. Somme totale des soldes");
        printf("\n\t\t\t\t\t\t\t\t7. Nombre total de comptes");
        printf("\n\t\t\t\t\t\t\t\t8. effectuer une transaction");
        printf("\n\t\t\t\t\t\t\t\t9. Quitter");
        printf("\n\n\t\t\t\t=============================================");
        printf("\n\n\t\t\t\t\tChoisissez parmi les options (1-8) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                nouveau_compte();
                break;

            case 2:
                modifier();
                break;

            case 3:
                consulter();
                break;

            case 4:
                effacer();
                break;

            case 5:
                afficher_liste();
                break;

            case 6:
                calculer_somme_soldes();
                break;

            case 7:
                afficher_nombre_total_comptes();
                break;
            case 8 :
                effectuer_transaction() ;

            case 9 :
                printf("Fermeture du programme. Merci !");
                break;

            default:
                printf("Choix invalide. Veuillez saisir un nombre entre 1 et 8.");
        }
    } while (choix != 8);
}

int main()
{
    char pass[10],password[10]="0000";
    int i=0;
    printf("\n\n\t\tEnter the password to login:  (entrer(0000)) :");
    //entrer 0000 comme mot de passe c'est juste pour formaliser la plateforme

    scanf("%s",pass);

    if (strcmp(pass,password)==0)
        {printf("\n\nPassword Match!\nLOADING");
        for(i=0;i<=6;i++)
        {

            printf(".");
        }
                system("cls");
            menu();
        }
    else
        {   printf("\n\nWrong password!!\a\a\a");
            login_try:
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {

                        system("cls");
                        main();
                    }

            else if (main_exit==0)
                    {
                    system("cls");
                    close();}
            else
                    {printf("\nInvalid!");
                    system("cls");
                    goto login_try;}

        }
        return 0;
}
