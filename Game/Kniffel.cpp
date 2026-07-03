#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define ERRORC() errorc(__FILE__, __LINE__)
const int WUERFEL = 5;
const int FELDER = 13;
int tutorial = 1;

typedef struct {
    int gesperrt[13];
    int zahlen[6];
    int dreierpasch;
    int viererpasch;
    int fullhouse;
    int kleineStrasse;
    int grosseStrasse;
    int kniffel;
    int chance;
}Punkteblock;

void credit();
void spielanleitung();
void errorc(const char* datei, int zeile);

void PDB_S(Punkteblock pb);
void PDB(Punkteblock pb);
void spielRunde_S(Punkteblock* pb);
void spielRunde_BE(Punkteblock* pb);
void spielRunde_BM(Punkteblock* pb);
void spielRunde_BS(Punkteblock* pb);

int awZahl(int wuerfel[WUERFEL], int zahl);
int awDreierpasch(int wuerfel[WUERFEL]);
int awViererpasch(int wuerfel[WUERFEL]);
int awFullHouse(int wuerfel[WUERFEL]);
int awKleineStrasse(int wuerfel[WUERFEL]);
int awgGrosseStrasse(int wuerfel[WUERFEL]);
int awKniffel(int wuerfel[WUERFEL]);
int awChance(int wuerfel[WUERFEL]);
int BGesamt(Punkteblock pb);

void berechneAllePunkte(int wuerfel[WUERFEL], int punkte[13]);
int waehleBesteKategorie(Punkteblock* pb, int punkte[13]);
void trageKategorieEin(Punkteblock* pb, int kategorie, int punkte[13]);

int main() {
    srand((unsigned int)time(NULL));

    while (1) {

        int taste;
        int wahl = 0;
        const char* menu[] = {
            " Start Game",
            " Einstellung",
            " Credits",
            " Spielanleitung",
            " Exit"
        };
        int size = sizeof(menu) / sizeof(menu[0]);
        while (1) {
            system("cls");
            printf("\n\n\n\t\t\t\t=========================================================                       V.0.0.4\n");
            printf("\t\t\t\t                      >  Kniffel  <\n");
            printf("\t\t\t\t=========================================================\n\n");
            for (int i = 0; i < size; i++) {
                if (i == wahl) printf("\t\t\t\t\t\t%s <- \n", menu[i]);
                else printf("\t\t\t\t\t\t %s\n", menu[i]);
            }

            taste = _getch();

            if (taste == 224) { // 224 steht für Prefix ist dafür da sonst pfeil taste hoch/runter machen kann
                taste = _getch();
                if (taste == 72 && wahl > 0) wahl--; // 72 steht für pfeil taste hoch
                if (taste == 80 && wahl < size - 1) wahl++; // 80 steht für pfeil taste runter
            }
            else if (taste == 13 || taste == ' ') { // 13 ist Enter
                break;
            }
            else {
                if ((taste == 'w' || taste == 'W') && wahl > 0) wahl--;
                if ((taste == 's' || taste == 'S') && wahl < size - 1) wahl++;
            }
        }

        if (wahl == 0) {

            int wrm = 1;

            do {

                int swahl = 0;
                const char* smenu[] = {
                    " Singleplayer",
                    " PvE",
                    " PvP",
                    "\n\t\t\t\t\t\t Zurueck"
                };
                int ssize = sizeof(smenu) / sizeof(smenu[0]);
                while (1) {
                    system("cls");
                    printf("\n\n\n\t\t\t\t=========================================================\n");
                    printf("\t\t\t\t             >  Waehlen Sie Ihren Modus aus  <\n");
                    printf("\t\t\t\t=========================================================\n\n");
                    for (int i = 0; i < ssize; i++) {
                        if (i == swahl) printf("\t\t\t\t\t\t%s <- \n", smenu[i]);
                        else printf("\t\t\t\t\t\t %s\n", smenu[i]);
                    }

                    taste = _getch();

                    if (taste == 224) {
                        taste = _getch();
                        if (taste == 72 && swahl > 0) swahl--;
                        if (taste == 80 && swahl < size - 1) swahl++;
                    }
                    else if (taste == 13 || taste == ' ') {
                        break;
                    }
                    else {
                        if ((taste == 'w' || taste == 'W') && swahl > 0) swahl--;
                        if ((taste == 's' || taste == 'S') && swahl < size - 1) swahl++;
                    }
                }

                if (swahl == 0) {

                    Punkteblock pb = { 0 };
                    ungetc('\n', stdin);
                    for (int runde = 0; runde < FELDER; runde++) {
                        system("cls");
                        printf("\n\t\t\t\t============== Runde %d ==============\n", runde + 1);
                        spielRunde_S(&pb);
                    }
                    while (getchar() != '\n');
                }

                else if (swahl == 1) {

                    int wrm_pve = 1;

                    do {

                        int pve_wahl = 0;
                        const char* pve_menu[] = {
                            " Einfach",
                            " Mittel",
                            " Schwer",
                            "\n\t\t\t\t\t\t Zurueck"
                        };
                        int pve_size = sizeof(pve_menu) / sizeof(pve_menu[0]);
                        while (1) {
                            system("cls");
                            printf("\n\n\n\t\t\t\t=========================================================\n");
                            printf("\t\t\t\t          >  waehlen sie die Schwierigkeit aus  <\n");
                            printf("\t\t\t\t=========================================================\n\n");
                            for (int i = 0; i < pve_size; i++) {
                                if (i == pve_wahl) printf("\t\t\t\t\t\t%s <- \n", pve_menu[i]);
                                else printf("\t\t\t\t\t\t %s\n", pve_menu[i]);
                            }

                            taste = _getch();

                            if (taste == 224) {
                                taste = _getch();
                                if (taste == 72 && pve_wahl > 0) pve_wahl--;
                                if (taste == 80 && pve_wahl < size - 1) pve_wahl++;
                            }
                            else if (taste == 13 || taste == ' ') {
                                break;
                            }
                            else {
                                if ((taste == 'w' || taste == 'W') && pve_wahl > 0) pve_wahl--;
                                if ((taste == 's' || taste == 'S') && pve_wahl < size - 1) pve_wahl++;
                            }
                        }

                        if (pve_wahl == 0) {

                            Punkteblock spieler = { 0 };
                            Punkteblock computer = { 0 };
                            ungetc('\n', stdin);
                            for (int runde = 0; runde < FELDER; runde++) {

                                system("cls");
                                if (runde != 0) {
                                    printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                    printf("\t\t\t\t                      Du bist am Zug                     \n");
                                    printf("\t\t\t\t=========================================================\n");
                                    Sleep(700);
                                    system("cls");
                                }
                                printf("\n\t\t\t\t============== Runde %d ==============\n", runde + 1);
                                spielRunde_S(&spieler);

                                system("cls");
                                printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t                   Computer ist am Zug                   \n");
                                printf("\t\t\t\t=========================================================\n");
                                Sleep(700);
                                system("cls");
                                spielRunde_BE(&computer);
                            }

                            int sum_s = BGesamt(spieler);
                            int sum_b = BGesamt(computer);


                            if (sum_s > sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Spieler gewinnt mit %d Punkten!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s < sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Computer gewinnt mit %d Punkten!\n", sum_b);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s == sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Unentschieden! Beide haben %d Punkte!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else {
                                ERRORC();
                                return 1;
                            }
                        }

                        else if (pve_wahl == 1) {

                            Punkteblock spieler = { 0 };
                            Punkteblock computer = { 0 };
                            ungetc('\n', stdin);
                            for (int runde = 0; runde < FELDER; runde++) {

                                system("cls");
                                if (runde != 0) {
                                    printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                    printf("\t\t\t\t                      Du bist am Zug                     \n");
                                    printf("\t\t\t\t=========================================================\n");
                                    Sleep(700);
                                    system("cls");
                                }
                                printf("\n\t\t\t\t============== Runde %d ==============\n", runde + 1);
                                spielRunde_S(&spieler);

                                system("cls");
                                printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t                   Computer ist am Zug                   \n");
                                printf("\t\t\t\t=========================================================\n");
                                Sleep(700);
                                system("cls");
                                spielRunde_BM(&computer);
                            }

                            int sum_s = BGesamt(spieler);
                            int sum_b = BGesamt(computer);


                            if (sum_s > sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Spieler gewinnt mit %d Punkten!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s < sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Computer gewinnt mit %d Punkten!\n", sum_b);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s == sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Unentschieden! Beide haben %d Punkte!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else {
                                ERRORC();
                                return 1;
                            }
                            while (getchar() != '\n');
                        }

                        else if (pve_wahl == 2) {

                            Punkteblock spieler = { 0 };
                            Punkteblock computer = { 0 };
                            ungetc('\n', stdin);
                            for (int runde = 0; runde < FELDER; runde++) {

                                system("cls");
                                if (runde != 0) {
                                    printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                    printf("\t\t\t\t                      Du bist am Zug                     \n");
                                    printf("\t\t\t\t=========================================================\n");
                                    Sleep(700);
                                    system("cls");
                                }
                                printf("\n\t\t\t\t============== Runde %d ==============\n", runde + 1);
                                spielRunde_S(&spieler);

                                system("cls");
                                printf("\n\n\n\n\n\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t                   Computer ist am Zug                   \n");
                                printf("\t\t\t\t=========================================================\n");
                                Sleep(700);
                                system("cls");
                                spielRunde_BS(&computer);
                            }

                            int sum_s = BGesamt(spieler);
                            int sum_b = BGesamt(computer);


                            if (sum_s > sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Spieler gewinnt mit %d Punkten!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s < sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Computer gewinnt mit %d Punkten!\n", sum_b);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else if (sum_s == sum_b) {
                                system("cls");
                                printf("\n\n\n\t\t\t\t=========================================================\n");
                                printf("\t\t\t\t         Unentschieden! Beide haben %d Punkte!\n", sum_s);
                                printf("\t\t\t\t=========================================================\n\n");
                                system("pause");
                            }
                            else {
                                ERRORC();
                                return 1;
                            }
                            while (getchar() != '\n');
                        }

                        else if (pve_wahl == 3) {

                            wrm_pve = 0;

                        }

                        else {
                            ERRORC();
                            return 1;
                        }

                    } while (wrm_pve == 1);

                }

                else if (swahl == 2) {

                    int ADS = 0;

                    do {
                        system("cls");
                        printf("\n\n\n\t\t\t\t=========================================================\n");
                        printf("\t\t\t\t          >  Wie viel Spieler sollen teilnehmen  <\n");
                        printf("\t\t\t\t=========================================================\n\n");
                        printf("\t\t\t\tGeben sie eine Zahl ein: ");
                        if (scanf_s("%d", &ADS) != 1 || ADS < 1) {
                            while (getchar() != '\n');
                            printf("\n\t\t\t\tBitte geben Sie eine positive Zahl ein.\n");
                            Sleep(1500);
                            ADS = 0;
                        }
                    } while (ADS < 1);

                    Punkteblock* spieler = (Punkteblock*)calloc(ADS, sizeof(Punkteblock));
                    if (!spieler) {
                        free(spieler);
                        spieler = NULL;
                        printf("\n\t\t\t\tFehler: Speicher konnte nicht reserviert werden\n");
                        system("pause");
                        ERRORC();
                        return 1;
                    }

                    for (int runde = 0; runde < FELDER; runde++) {
                        for (int sp = 0; sp < ADS; sp++) {
                            system("cls");
                            printf("\n\t\t\t\tSpieler %d ist am Zug (Runde %d)\n", sp + 1, runde + 1);
                            spielRunde_S(&spieler[sp]);
                        }
                    }

                    int maxPunkte = 0;
                    int gewinner = 0;

                    for (int sp = 0; sp < ADS; sp++) {
                        system("cls");
                        printf("\n\t\t\t\tSpieler %d Punkteblock:\n", sp + 1);
                        PDB(spieler[sp]);

                        int sum = BGesamt(spieler[sp]);

                        if (sum > maxPunkte) {
                            maxPunkte = sum;
                            gewinner = sp;
                        }
                        system("pause");
                    }

                    system("cls");
                    printf("\n\n\n\t\t\t\t=========================================================\n");
                    printf("\n\t\t\t         Spieler %d gewinnt mit %d Punkten!\n", gewinner + 1, maxPunkte);
                    printf("\t\t\t\t=========================================================\n\n");
                    system("pause");

                    free(spieler);
                    spieler = NULL;
                    while (getchar() != '\n');
                }

                else if (swahl == 3) {

                    wrm = 0;

                }

                else {
                    ERRORC();
                    return 1;
                }

            } while (wrm == 1);

        }

        else if (wahl == 1) {
            int ewahl = 0;
            const char* emenu[] = {
            " Tutorial: ",
            "\n\t\t\t\t\t\t Zurueck"
            };
            int esize = sizeof(emenu) / sizeof(emenu[0]);
            int etaste;

            while (1) {
                system("cls");
                printf("\n\n\n\t\t\t\t=========================================================                       V.0.0.4\n");
                printf("\t\t\t\t                      >  Kniffel  <\n");
                printf("\t\t\t\t=========================================================\n\n");
                const char* checkbox = (tutorial == 1) ? "[X]" : "[ ]";
                for (int i = 0; i < esize; i++) {
                    if (i == 0) {
                        if (i == ewahl) printf("\t\t\t\t\t\t%s%s <- \n", emenu[i], checkbox);
                        else printf("\t\t\t\t\t\t %s%s\n", emenu[i], checkbox);
                    }
                    else {
                        if (i == ewahl) printf("\t\t\t\t\t\t%s <- \n", emenu[i]);
                        else printf("\t\t\t\t\t\t %s\n", emenu[i]);
                    }
                }

                etaste = _getch();

                if (etaste == 224) {
                    etaste = _getch();
                    if (etaste == 72 && ewahl > 0) ewahl--;
                    if (etaste == 80 && ewahl < esize - 1) ewahl++;
                }
                else if (etaste == 13 || etaste == ' ') {
                    if (ewahl == 0) {
                        tutorial = !tutorial;
                        Sleep(100);
                    }
                    if (ewahl == 1) break;
                }
                else {
                    if ((etaste == 'w' || etaste == 'W') && ewahl > 0) ewahl--;
                    if ((etaste == 's' || etaste == 'S') && ewahl < esize - 1) ewahl++;
                }
            }
        }

        else if (wahl == 2) {
            credit();
        }

        else if (wahl == 3) {

            spielanleitung();

        }

        else if (wahl == 4) {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\033[1;37m__________________________________________\033[0m\n\n");
            printf("\t\t\t\t\t\033[1;37m         >  Danke fuers Spielen!  <\033[0m\n\n");
            printf("\t\t\t\t\t\033[1;37m__________________________________________\033[0m\n\n\n\n\n\n\n\n\n\n\n\n\n");
            Sleep(2000);
            return 0;
        }

        else {
            ERRORC();
            return 1;
        }

    }

    return 1;
}

void credit() {

    system("cls");
    printf("\n\n\t\t\t\t  ====================================================\n");
    printf("\t\t\t\t                        Credits \n");
    printf("\t\t\t\t  ====================================================\n\n\n");
    Sleep(400);
    printf("\t\t\t\t\t------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t\t        Projektinformationen\n");
    Sleep(100);
    printf("\t\t\t\t\t------------------------------------\n\n");
    Sleep(100);
    printf("\t\t\t\t\tTitel: Kniffel\n");
    Sleep(100);
    printf("\t\t\t\t\tVersion: 0.0.0\n");
    Sleep(100);
    printf("\t\t\t\t\tKurzbeschreibung: Das ist ein Wuerfel Spiel\n\n\n");
    Sleep(100);

    printf("\t\t\t\t\t------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t\t         Entwicklerteam\n");
    Sleep(100);
    printf("\t\t\t\t\t------------------------------------\n\n");
    Sleep(100);
    printf("\t\t\t\t\tProgrammierer: Name\n");
    Sleep(100);
    printf("\t\t\t\t\tDesigner: Name\n");
    Sleep(100);

    printf("\t\t\t\t\t------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t\t        Ressourcen & Tools\n");
    Sleep(100);
    printf("\t\t\t\t\t------------------------------------\n\n");
    Sleep(100);
    printf("\t\t\t\t\tProgrammiersprachen: C\n");
    Sleep(100);
    printf("\t\t\t\t\tEngines: Visual Studio\n");
    Sleep(100);
    printf("\t\t\t\t\tBibliotheken: stdio.h, stdlib.h,\n");
    printf("\t\t\t\t\t              time.h, windows.h,\n\n\n");
    printf("\t\t\t\t\t              conio.h,\n\n\n");
    Sleep(100);

    printf("\t\t\t\t\t------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t\t            Danksagungen\n");
    Sleep(100);
    printf("\t\t\t\t\t------------------------------------\n\n");
    Sleep(100);
    printf("\t\t\t\t\tNoch Nimand\n\n");
    Sleep(100);

    system("pause");

}
void spielanleitung() {

    system("cls");
    printf("\n\n\t\t\t\t============================================================\n");
    printf("\t\t\t\t                    KNIFFEL - SPIELANLEITUNG\n");
    printf("\t\t\t\t============================================================\n\n");
    Sleep(400);

    printf("\t\t\t\tWAS IST KNIFFEL?\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tKniffel ist ein Wuerfelspiel fuer 1 oder mehrere Spieler.\n");
    Sleep(100);
    printf("\t\t\t\tZiel ist es, moeglichst viele Punkte zu sammeln.\n");
    Sleep(100);
    printf("\t\t\t\tGespielt wird mit 5 Wuerfeln ueber genau 13 Runden.\n\n");
    Sleep(100);

    printf("\t\t\t\tSPIELABLAUF (GANZ EINFACH ERKLAERT):\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t1. Eine Runde beginnt.\n");
    Sleep(100);
    printf("\t\t\t\t2. Du wuerfelst mit allen 5 Wuerfeln.\n");
    Sleep(100);
    printf("\t\t\t\t3. Du darfst insgesamt BIS ZU 3 MAL wuerfeln.\n");
    Sleep(100);
    printf("\t\t\t\t4. Nach jedem Wurf kannst du entscheiden:\n");
    Sleep(100);
    printf("\t\t\t\t   - Welche Wuerfel du BEHALTEN willst\n");
    Sleep(100);
    printf("\t\t\t\t   - Welche Wuerfel du NEU wuerfeln willst\n");
    Sleep(100);
    printf("\t\t\t\t5. Nach dem letzten Wurf musst du eine Kategorie waehlen.\n");
    Sleep(100);
    printf("\t\t\t\t6. Diese Kategorie ist danach gesperrt.\n\n");
    Sleep(100);

    printf("\t\t\t\tBEISPIEL FUER DAS WUERFELN:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\t1. Wurf:  [1] [3] [3] [5] [6]\n");
    Sleep(100);
    printf("\t\t\t\tDu willst die beiden 3er behalten.\n");
    Sleep(100);
    printf("\t\t\t\t2. Wurf:  [3] [3] [2] [3] [5]\n");
    Sleep(100);
    printf("\t\t\t\tJetzt hast du drei 3er.\n");
    Sleep(100);
    printf("\t\t\t\tDu kannst nochmal wuerfeln oder stoppen.\n\n");
    Sleep(100);

    printf("\t\t\t\tDIE OBEREN FELDER (ZAHLEN 1 BIS 6):\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tEinser   : Alle 1er zaehlen (z.B. 1+1 = 2 Punkte)\n");
    Sleep(100);
    printf("\t\t\t\tZweier   : Alle 2er zaehlen\n");
    Sleep(100);
    printf("\t\t\t\tDreier   : Alle 3er zaehlen\n");
    Sleep(100);
    printf("\t\t\t\tVierer   : Alle 4er zaehlen\n");
    Sleep(100);
    printf("\t\t\t\tFuenfer  : Alle 5er zaehlen\n");
    Sleep(100);
    printf("\t\t\t\tSechser  : Alle 6er zaehlen\n\n");
    Sleep(100);

    printf("\t\t\t\tBONUSREGEL:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tWenn die Summe von Einser bis Sechser mindestens 63 Punkte ist,\n");
    Sleep(100);
    printf("\t\t\t\tbekommst du AUTOMATISCH 35 Bonuspunkte.\n\n");
    Sleep(100);

    printf("\t\t\t\tDIE UNTEREN FELDER:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tDreierpasch  : Mindestens 3 gleiche Wuerfel\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = Summe aller Wuerfel\n\n");
    Sleep(100);

    printf("\t\t\t\tViererpasch  : Mindestens 4 gleiche Wuerfel\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = Summe aller Wuerfel\n\n");
    Sleep(100);

    printf("\t\t\t\tFull House   : 3 gleiche + 2 gleiche Wuerfel\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = 25\n");
    Sleep(100);
    printf("\t\t\t\t               Beispiel: 3,3,3,5,5\n\n");
    Sleep(100);

    printf("\t\t\t\tKleine Strase: 4 Zahlen in Reihenfolge\n");
    Sleep(100);
    printf("\t\t\t\t               Beispiel: 1,2,3,4\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = 30\n\n");
    Sleep(100);

    printf("\t\t\t\tGrosse Strase: 5 Zahlen in Reihenfolge\n");
    Sleep(100);
    printf("\t\t\t\t               Beispiel: 2,3,4,5,6\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = 40\n\n");
    Sleep(100);

    printf("\t\t\t\tKniffel      : Alle 5 Wuerfel gleich\n");
    Sleep(100);
    printf("\t\t\t\t               Beispiel: 6,6,6,6,6\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = 50\n\n");
    Sleep(100);

    printf("\t\t\t\tChance       : Beliebige Kombination\n");
    Sleep(100);
    printf("\t\t\t\t               Punkte = Summe aller Wuerfel\n\n");
    Sleep(100);

    printf("\t\t\t\tEXTRA-KNIFFEL:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tWenn du MEHR ALS EINEN Kniffel wuerfelst,\n");
    Sleep(100);
    printf("\t\t\t\tdarfst du SELBST entscheiden,\n");
    Sleep(100);
    printf("\t\t\t\tin welche Kategorie du ihn eintraegst.\n\n");
    Sleep(100);

    printf("\t\t\t\tSPIELENDE:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tNach 13 Runden werden alle Punkte zusammengezaehlt.\n");
    Sleep(100);
    printf("\t\t\t\tBonus wird dazu gerechnet.\n");
    Sleep(100);
    printf("\t\t\t\tDer Spieler mit den meisten Punkten gewinnt.\n\n");
    Sleep(100);

    printf("\t\t\t\tMERKSATZ:\n");
    Sleep(100);
    printf("\t\t\t\t------------------------------------------------------------\n");
    Sleep(100);
    printf("\t\t\t\tBehalte gute Wuerfel, denke voraus und waehle deine Kategorie klug!\n\n");
    Sleep(100);

    system("pause");
}
void errorc(const char* datei, int zeile) {
    system("cls");
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t=========================================================\n");
    printf("\t\t\t\tLeider ist ein Fehler aufgetreten.\n");
    printf("\t\t\t\tBitte versuchen Sie es erneut.\n");
    printf("\t\t\t\tFehlercode in:\n");
    printf("\t\t\t\tZeile %d\n", zeile);
    printf("\t\t\t\tDatei %s\n", datei);
    printf("\t\t\t\t=========================================================\n\n\n\n");
}

void PDB_S(Punkteblock pb) {

    int sum = 0;
    printf("\n\t\t\t\t==================== PUNKTEBLOCK ====================\n");
    printf("\t\t\t\t| Kategorie            | Punkte                     |\n");
    printf("\t\t\t\t-----------------------------------------------------\n");

    printf("\t\t\t\t| 1.  Einser           | %3d |                      |\n", pb.zahlen[0]);
    printf("\t\t\t\t| 2.  Zweier           | %3d |                      |\n", pb.zahlen[1]);
    printf("\t\t\t\t| 3.  Dreier           | %3d |                      |\n", pb.zahlen[2]);
    printf("\t\t\t\t| 4.  Vierer           | %3d |                      |\n", pb.zahlen[3]);
    printf("\t\t\t\t| 5.  Fuenfer          | %3d |                      |\n", pb.zahlen[4]);
    printf("\t\t\t\t| 6.  Sechser          | %3d |                      |\n", pb.zahlen[5]);

    for (int i = 0; i < 6; i++) {
        sum += pb.zahlen[i];
    }
    int bonus = (sum >= 63) ? 35 : 0;
    printf("\t\t\t\t| BonusPunkte          | %3d |                      |\n", bonus);

    printf("\t\t\t\t-----------------------------------------------------\n");

    printf("\t\t\t\t| 7.  Dreierpasch      | %3d |                      |\n", pb.dreierpasch);
    printf("\t\t\t\t| 8.  Viererpasch      | %3d |                      |\n", pb.viererpasch);
    printf("\t\t\t\t| 9.  Full House       | %3d |                      |\n", pb.fullhouse);
    printf("\t\t\t\t| 10. Kleine Strasse   | %3d |                      |\n", pb.kleineStrasse);
    printf("\t\t\t\t| 11. Grosse Strasse   | %3d |                      |\n", pb.grosseStrasse);
    printf("\t\t\t\t| 12. Kniffel          | %3d |                      |\n", pb.kniffel);
    printf("\t\t\t\t| 13. Chance           | %3d |                      |\n", pb.chance);

    int gesamt = sum;
    int untere[7] = { pb.dreierpasch, pb.viererpasch, pb.fullhouse,
                  pb.kleineStrasse, pb.grosseStrasse, pb.kniffel, pb.chance };
    for (int i = 0; i < 7; i++) {
        gesamt += untere[i];
    }

    printf("\t\t\t\t=====================================================\n");
    printf("\t\t\t\t| Gesamtpunktzahl      | %3d |                      |\n", gesamt + bonus);
    printf("\t\t\t\t=====================================================\n\n");

}
void PDB(Punkteblock pb) {

    system("cls");
    int sum = 0;
    printf("\n\t\t\t\t==================== PUNKTEBLOCK ====================\n");
    printf("\t\t\t\t| Kategorie        | Punkte                         |\n");
    printf("\t\t\t\t-----------------------------------------------------\n");

    printf("\t\t\t\t| Einser           | %3d |                          |\n", pb.zahlen[0]);
    printf("\t\t\t\t| Zweier           | %3d |                          |\n", pb.zahlen[1]);
    printf("\t\t\t\t| Dreier           | %3d |                          |\n", pb.zahlen[2]);
    printf("\t\t\t\t| Vierer           | %3d |                          |\n", pb.zahlen[3]);
    printf("\t\t\t\t| Fuenfer          | %3d |                          |\n", pb.zahlen[4]);
    printf("\t\t\t\t| Sechser          | %3d |                          |\n", pb.zahlen[5]);

    for (int i = 0; i < 6; i++) {
        sum += pb.zahlen[i];
    }
    int bonus = (sum >= 63) ? 35 : 0;
    printf("\t\t\t\t| BonusPunkte      | %3d |                          |\n", bonus);

    printf("\t\t\t\t-----------------------------------------------------\n");

    printf("\t\t\t\t| Dreierpasch      | %3d |                          |\n", pb.dreierpasch);
    printf("\t\t\t\t| Viererpasch      | %3d |                          |\n", pb.viererpasch);
    printf("\t\t\t\t| Full House       | %3d |                          |\n", pb.fullhouse);
    printf("\t\t\t\t| Kleine Strasse   | %3d |                          |\n", pb.kleineStrasse);
    printf("\t\t\t\t| Grosse Strasse   | %3d |                          |\n", pb.grosseStrasse);
    printf("\t\t\t\t| Kniffel          | %3d |                          |\n", pb.kniffel);
    printf("\t\t\t\t| Chance           | %3d |                          |\n", pb.chance);

    int gesamt = sum;
    int untere[7] = { pb.dreierpasch, pb.viererpasch, pb.fullhouse,
                  pb.kleineStrasse, pb.grosseStrasse, pb.kniffel, pb.chance };
    for (int i = 0; i < 7; i++) {
        gesamt += untere[i];
    }

    printf("\t\t\t\t=====================================================\n");
    printf("\t\t\t\t| Gesamtpunktzahl  | %3d |                          |\n", gesamt + bonus);
    printf("\t\t\t\t=====================================================\n\n");

}
void spielRunde_S(Punkteblock* pb) {

    int wuerfel[WUERFEL] = { 0 };
    int behalten[WUERFEL] = { 0 };
    int wurf = 0;

    while (wurf < 3) {

        for (int i = 0; i < WUERFEL; i++) if (!behalten[i]) wuerfel[i] = (rand() % 6) + 1;

        printf("\n\t\t\t\tWurf %d: ", wurf + 1);
        for (int i = 0; i < WUERFEL; i++) printf(" [%d] ", wuerfel[i]);

        if (wurf < 2) {
            char eingabe[WUERFEL * 3];

            while (getchar() != '\n');

            if (tutorial == 1) printf("\n\t\t\t\tWelche Wuerfel behalten?\n\t\t\t\t(Die position des wuerfes wird angegeben)\n\t\t\t\t(z.B. 1 3 5 oder Enter zum weiterwuerfeln): ");
            else printf("\n\t\t\t\tWelche Wuerfel behalten: ");

            if (fgets(eingabe, sizeof(eingabe), stdin) != 0) {

                if (eingabe[0] != '\n') {

                    for (int i = 0; i < WUERFEL; i++) behalten[i] = 0;

                    for (int i = 0; i < (int)strlen(eingabe); i++) {
                        if (eingabe[i] >= '1' && eingabe[i] <= '5') {
                            int num = eingabe[i] - '0';
                            behalten[num - 1] = 1;
                        }
                    }
                }
            }
            ungetc('\n', stdin);
        }
        wurf++;
    }

    int kategorie = 0;
    do {

        system("cls");
        printf("\n\t\t\t\tDeine Wuerfeln: ");
        for (int i = 0; i < WUERFEL; i++) printf(" [%d] ", wuerfel[i]);
        printf("\n");
        PDB_S(*pb);
        printf("\t\t\t\tWaehlen Sie eine Option aus (1-13): ");

        if (scanf_s("%d", &kategorie) != 1) {
            while (getchar() != '\n');
            kategorie = 0;
            system("cls");
        }

        if (kategorie >= 1 && kategorie <= 13 && pb->gesperrt[kategorie - 1]) {
            printf("\n\t\t\t\tSie haben diese Kategorie bereits ausgewaehlt.\n");
            system("pause");
            kategorie = 0;
        }

    } while (kategorie < 1 || kategorie > 13);
    kategorie--;

    if (kategorie < 6) pb->zahlen[kategorie] = awZahl(wuerfel, kategorie + 1);
    else if (kategorie == 6) pb->dreierpasch = awDreierpasch(wuerfel);
    else if (kategorie == 7) pb->viererpasch = awViererpasch(wuerfel);
    else if (kategorie == 8) pb->fullhouse = awFullHouse(wuerfel);
    else if (kategorie == 9) pb->kleineStrasse = awKleineStrasse(wuerfel);
    else if (kategorie == 10) pb->grosseStrasse = awgGrosseStrasse(wuerfel);
    else if (kategorie == 11) pb->kniffel = awKniffel(wuerfel);
    else if (kategorie == 12) pb->chance = awChance(wuerfel);
    else ERRORC();
    pb->gesperrt[kategorie] = 1;

    system("cls");
    PDB(*pb);
    system("pause");
}
void spielRunde_BE(Punkteblock* pb) {

    int wuerfel[WUERFEL] = { 0 };

    for (int i = 0; i < WUERFEL; i++) wuerfel[i] = (rand() % 6) + 1;

    for (int k = 0; k < 13; k++) {
        if (!pb->gesperrt[k]) {

            if (k < 6) pb->zahlen[k] = awZahl(wuerfel, k + 1);
            else if (k == 6) pb->dreierpasch = awDreierpasch(wuerfel);
            else if (k == 7) pb->viererpasch = awViererpasch(wuerfel);
            else if (k == 8) pb->fullhouse = awFullHouse(wuerfel);
            else if (k == 9) pb->kleineStrasse = awKleineStrasse(wuerfel);
            else if (k == 10) pb->grosseStrasse = awgGrosseStrasse(wuerfel);
            else if (k == 11) pb->kniffel = awKniffel(wuerfel);
            else if (k == 12) pb->chance = awChance(wuerfel);

            pb->gesperrt[k] = 1;
            break;
        }
    }
    system("cls");
    PDB(*pb);
    system("pause");
}
void spielRunde_BM(Punkteblock* pb) {

    int wuerfel[WUERFEL];
    int punkte[13];

    for (int i = 0; i < WUERFEL; i++) wuerfel[i] = (rand() % 6) + 1;

    berechneAllePunkte(wuerfel, punkte);
    int k = waehleBesteKategorie(pb, punkte);
    trageKategorieEin(pb, k, punkte);

    system("cls");
    PDB(*pb);
    system("pause");

}
void spielRunde_BS(Punkteblock* pb) {

    int versuch = 0;
    while (versuch < 1000) {
        int k = rand() % 13;
        int z = 0;
        if (k == 0 && !pb->gesperrt[0]) {
            pb->zahlen[0] = (rand() % 6) + 1;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 1 && !pb->gesperrt[1]) {
            z = (rand() % 6) + 1;
            if (z == 1) pb->zahlen[1] = 2;
            else if (z == 2) pb->zahlen[1] = 4;
            else if (z == 3) pb->zahlen[1] = 6;
            else if (z == 4) pb->zahlen[1] = 8;
            else if (z == 5) pb->zahlen[1] = 10;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 2 && !pb->gesperrt[2]) {
            z = (rand() % 6) + 1;
            if (z == 1) pb->zahlen[2] = 3;
            else if (z == 2) pb->zahlen[2] = 6;
            else if (z == 3) pb->zahlen[2] = 9;
            else if (z == 4) pb->zahlen[2] = 12;
            else if (z == 5) pb->zahlen[2] = 15;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 3 && !pb->gesperrt[3]) {
            z = (rand() % 6) + 1;
            if (z == 1) pb->zahlen[3] = 4;
            else if (z == 2) pb->zahlen[3] = 8;
            else if (z == 3) pb->zahlen[3] = 12;
            else if (z == 4) pb->zahlen[3] = 16;
            else if (z == 5) pb->zahlen[3] = 20;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 4 && !pb->gesperrt[4]) {
            z = (rand() % 6) + 1;
            if (z == 1) pb->zahlen[4] = 5;
            else if (z == 2) pb->zahlen[4] = 10;
            else if (z == 3) pb->zahlen[4] = 15;
            else if (z == 4) pb->zahlen[4] = 20;
            else if (z == 5) pb->zahlen[4] = 25;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 5 && !pb->gesperrt[5]) {
            z = (rand() % 6) + 1;
            if (z == 1) pb->zahlen[5] = 6;
            else if (z == 2) pb->zahlen[5] = 12;
            else if (z == 3) pb->zahlen[5] = 18;
            else if (z == 4) pb->zahlen[5] = 24;
            else if (z == 5) pb->zahlen[5] = 30;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 6 && !pb->gesperrt[6]) {
            pb->dreierpasch = (rand() % 21) + 5 + 5;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 7 && !pb->gesperrt[7]) {
            pb->viererpasch = (rand() % 21) + 5 + 5;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 8 && !pb->gesperrt[8]) {
            z = (rand() % 2);
            pb->fullhouse = (z == 0) ? 25 : 0;;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 9 && !pb->gesperrt[9]) {
            z = (rand() % 2);
            pb->kleineStrasse = (z == 1) ? 30 : 0;;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 10 && !pb->gesperrt[10]) {
            z = (rand() % 3);
            pb->grosseStrasse = (z == 1) ? 40 : 0;;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 11 && !pb->gesperrt[11]) {
            z = (rand() % 4);
            pb->kniffel = (z == 2) ? 50 : 0;
            pb->gesperrt[k] = 1;
            break;
        }
        else if (k == 12 && !pb->gesperrt[12]) {
            pb->chance = (rand() % 21) + 5 + 5;
            pb->gesperrt[k] = 1;
            break;
        }
        versuch++;
    }
    system("cls");
    PDB(*pb);
    system("pause");
}

int awZahl(int wuerfel[WUERFEL], int zahl) {
    int sum = 0;
    for (int i = 0; i < WUERFEL; i++) {
        if (wuerfel[i] == zahl)
            sum += zahl;
    }
    return sum;
}
int awDreierpasch(int wuerfel[WUERFEL]) {
    int zZ[7] = { 0 };

    for (int i = 0; i < WUERFEL; i++) zZ[wuerfel[i]]++;

    for (int i = 1; i < 7; i++) {
        if (zZ[i] >= 3) {
            int summe = 0;
            for (int j = 0; j < WUERFEL; j++) summe += wuerfel[j];
            return summe;
        }
    }
    return 0;
}
int awViererpasch(int wuerfel[WUERFEL]) {
    int zZ[7] = { 0 };

    for (int i = 0; i < WUERFEL; i++) zZ[wuerfel[i]]++;

    for (int i = 1; i < 7; i++) {
        if (zZ[i] >= 4) {
            int summe = 0;
            for (int j = 0; j < WUERFEL; j++) summe += wuerfel[j];
            return summe;
        }
    }
    return 0;
}
int awFullHouse(int wuerfel[WUERFEL]) {

    int zZ[7] = { 0 };

    for (int i = 0; i < WUERFEL; i++) zZ[wuerfel[i]]++;

    /* Alte Variante
    for (int i = 1; i < 7; i++) {
        if (zZ[i] >= 3) {
            zZ[i] = 0;
            for (int i = 1; i < 7; i++) {
                if (zZ[i] >= 2) {
                    return 25;
                }
            }
        }
    }
    */

    for (int drei = 1; drei < 7; drei++) {
        if (zZ[drei] >= 3) {
            for (int zwei = 1; zwei < 7; zwei++) {
                if (zwei != drei && zZ[zwei] >= 2) {
                    return 25;
                }
            }
        }
    }

    return 0;
}
int awKleineStrasse(int wuerfel[WUERFEL]) {

    int zZ[7] = { 0 };

    for (int i = 0; i < WUERFEL; i++) zZ[wuerfel[i]]++;

    if ((zZ[1] && zZ[2] && zZ[3] && zZ[4]) ||
        (zZ[2] && zZ[3] && zZ[4] && zZ[5]) ||
        (zZ[3] && zZ[4] && zZ[5] && zZ[6])) return 30;

    return 0;
}
int awgGrosseStrasse(int wuerfel[WUERFEL]) {

    int zZ[7] = { 0 };

    for (int i = 0; i < WUERFEL; i++) zZ[wuerfel[i]]++;

    if ((zZ[1] && zZ[2] && zZ[3] && zZ[4] && zZ[5]) ||
        (zZ[2] && zZ[3] && zZ[4] && zZ[5] && zZ[6])) return 40;

    return 0;
}
int awKniffel(int wuerfel[WUERFEL]) {

    for (int i = 1; i < WUERFEL; i++) {
        if (wuerfel[i] != wuerfel[0]) return 0;
    }
    return 50;
}
int awChance(int wuerfel[WUERFEL]) {

    int sum = 0;

    for (int i = 0; i < WUERFEL; i++) sum += wuerfel[i];

    return sum;
}
int BGesamt(Punkteblock pb) {
    int sum = 0;

    for (int i = 0; i < 6; i++) sum += pb.zahlen[i];
    int bonus = (sum >= 63) ? 35 : 0;

    sum += pb.dreierpasch + pb.viererpasch + pb.fullhouse +
        pb.kleineStrasse + pb.grosseStrasse +
        pb.kniffel + pb.chance;

    return sum + bonus;
}

void berechneAllePunkte(int wuerfel[WUERFEL], int punkte[13]) {

    for (int i = 0; i < 6; i++) punkte[i] = awZahl(wuerfel, i + 1);
    punkte[6] = awDreierpasch(wuerfel);
    punkte[7] = awViererpasch(wuerfel);
    punkte[8] = awFullHouse(wuerfel);
    punkte[9] = awKleineStrasse(wuerfel);
    punkte[10] = awgGrosseStrasse(wuerfel);
    punkte[11] = awKniffel(wuerfel);
    punkte[12] = awChance(wuerfel);

}
int waehleBesteKategorie(Punkteblock* pb, int punkte[13]) {

    int bz = -1;
    int bk = -1;

    for (int i = 0; i < 13; i++) {

        int a = punkte[i];
        if (bz < punkte[i] && !pb->gesperrt[i]) {
            bz = punkte[i];
            bk = i;
        }
    }

    return bk;
}
void trageKategorieEin(Punkteblock* pb, int k, int punkte[13]) {

    if (k < 6) pb->zahlen[k] = punkte[k];
    else if (k == 6) pb->dreierpasch = punkte[6];
    else if (k == 7) pb->viererpasch = punkte[7];
    else if (k == 8) pb->fullhouse = punkte[8];
    else if (k == 9) pb->kleineStrasse = punkte[9];
    else if (k == 10) pb->grosseStrasse = punkte[10];
    else if (k == 11) pb->kniffel = punkte[11];
    else if (k == 12) pb->chance = punkte[12];

    pb->gesperrt[k] = 1;
}