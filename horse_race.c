#include<ncurses.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int won;
int race_length;
pthread_mutex_t print_mutex;

struct horse_t {
        char name[50];
        int pos;
        int odds;
} horses[5];

void finish() {
        endwin();
        pthread_mutex_destroy(&print_mutex);
        exit(0);
}

void print_finish() {
        int j;
        printw("                        |");
        for (j = 0; j < race_length; j++) {
                printw("  ");
        }
        printw("|\n");
        return;
}

int compare(const void *s1, const void *s2) {
        struct horse_t *horse1 = (struct horse_t *) s1;
        struct horse_t *horse2 = (struct horse_t *) s2;

        return horse2->pos - horse1->pos;
}

void print_standings() {
        int i;
        struct horse_t horse_list[5];

        for (i = 0; i < 5; i++) {
                strcpy(horse_list[i].name, horses[i].name);
                horse_list[i].pos = horses[i].pos;
                horse_list[i].odds = horses[i].odds;
        }

        qsort(horse_list, 5, sizeof(struct horse_t), compare);
        
        printw("Standings:\n");
        printw("1st: %s\n", horse_list[0].name);
        printw("2nd: %s\n", horse_list[1].name);
        printw("3rd: %s\n", horse_list[2].name);
        printw("4th: %s\n", horse_list[3].name);
        printw("5th: %s\n", horse_list[4].name);
}

void print_odds() {
        int i;
        printw("Odds:\n");
        for (i = 0; i < 5; i++) {
                printw("%s: %d-1\n", horses[i].name, horses[i].odds);
        }
}

void print_title() {
        printw("    __  __                        ____             _            \n");
        printw("   / / / /___  _____________     / __ \\____ ______(_)___  ____ _\n");
        printw("  / /_/ / __ \\/ ___/ ___/ _ \\   / /_/ / __ `/ ___/ / __ \\/ __ `/\n");
        printw(" / __  / /_/ / /  (__  )  __/  / _, _/ /_/ / /__/ / / / / /_/ / \n");
        printw("/_/ /_/\\____/_/  /____/\\___/  /_/ |_|\\__,_/\\___/_/_/ /_/\\__, /  \n");
        printw("                                                       /____/   \n");
        printw("-------------------------------------------------------------------------------\n");
}

void printscr(int idx) {
        int i;
        int j;
        pthread_mutex_lock(&print_mutex);

        clear();
        print_title();
        print_finish();
        for (i = 0; i < 5; i++) {

                for (j = 0; j < horses[i].pos; j++) {
                        printw("  ");
                }
                printw("%s: x\n", horses[i].name);

                print_finish();
        }
        printw("-------------------------------------------------------------------------------\n");
        print_standings();
        printw("----------\n");
        print_odds();
        if(horses[idx].pos > race_length && won == -1) {
                printw("\n\n%s has won!!! (Press a key to exit)\n", horses[idx].name);
                won = idx;
                getch();
                finish();
        } 
        refresh();
        
        pthread_mutex_unlock(&print_mutex);
        return;
}

void * horse(void * arg) {
        int idx = *((int *) arg);
        free(arg);

        int odds = horses[idx].odds;

        horses[idx].pos = 0;
        while (1) {
                if (odds % 2 == 0) {
                        sleep(rand() % (odds/2 + 1) + 1);
                } else {
                        if (rand() % 2 == 0) {
                                sleep(rand() % (odds/2 + 1) + 1);
                        } else {
                                sleep(rand() % ((odds + 1)/2 + 1) + 1);
                        }
                } 
                horses[idx].pos++;
                printscr(idx);
        }
}

void get_horse_name(struct horse_t * horse){
        const char *adj[46] = {
                                  "Lightning",
                                  "Bold",
                                  "Salsa",
                                  "Sunny with a",
                                  "The Only",
                                  "Georgia's",
                                  "Tennessee",
                                  "Screamin'",
                                  "Cow",
                                  "Fast",
                                  "Hairy",
                                  "Tubby",
                                  "Jumpin'",
                                  "For",
                                  "Hangin' with",
                                  "Portland",
                                  "Humboldt",
                                  "Cheesy",
                                  "Bright",
                                  "Flat",
                                  "Pancake",
                                  "Jelly-Filled",
                                  "Evil",
                                  "Nice",
                                  "Slim",
                                  "Bet on",
                                  "Don't Forget",
                                  "Sexy",
                                  "Lucky",
                                  "Lovely",
                                  "Smokey",
                                  "Handsome",
                                  "Snatchin'",
                                  "Hungry",
                                  "Fiesta",
                                  "Chips 'n",
                                  "Topdecked",
                                  "Party with",
                                  "The lonely",
                                  "Half",
                                  "Super",
                                  "Racin'",
                                  "Wrastlin'",
                                  "Kentucky",
                                  "Roses are",
                                  "Dinner with"
                              };
        const char *nouns[66] = {
                                    "Lightning",
                                    "Salsa",
                                    "Chance",
                                    "Tennessee",
                                    "Pride",
                                    "Georgia",
                                    "Bryan",
                                    "Void",
                                    "Icehowl",
                                    "Cowboy",
                                    "Git Commit",
                                    "Mexican",
                                    "Butter",
                                    "Cat Woman",
                                    "Comcast",
                                    "Anderson",
                                    "Mango",
                                    "Mouse",
                                    "America",
                                    "Body Mass",
                                    "Hippo",
                                    "Meat",
                                    "Robot",
                                    "Gary",
                                    "Scout",
                                    "Franky",
                                    "Bella",
                                    "Tank",
                                    "Gus",
                                    "Nostalgia",
                                    "Dancer",
                                    "Blue",
                                    "Pop",
                                    "Ma",
                                    "Bush",
                                    "Reagan",
                                    "Zippo",
                                    "Love",
                                    "Mario",
                                    "Red",
                                    "Dan",
                                    "Biscuit",
                                    "Superman",
                                    "Winner",
                                    "Insurance",
                                    "Lightbulb",
                                    "Morning",
                                    "Baby",
                                    "Wizard",
                                    "Diablo",
                                    "Blueberry",
                                    "Apple",
                                    "Hank",
                                    "Taco",
                                    "Honey",
                                    "Toe-jam",
                                    "Rock",
                                    "Licky",
                                    "Horse",
                                    "Banjo",
                                    "Lost Love",
                                    "Egyptian",
                                    "Vodka",
                                    "Rum",
                                    "Cider",
                                    "Trouble"
                                };

        char name[50] = "";
        if (rand() % 3 > 0){
                strcat(name, adj[rand() % 46]);
                strcat(name, " ");
        }

        strcat(name, nouns[rand() % 66]);
        int length = strlen(name);

        int i;
        // longest name is: "Sunny with a Lightning" (22 chars) don't judge me
        char name_with_spaces[23] = "";
        for (i = 0; i < 22 - length; i++)  {
                strcat(name_with_spaces, " ");
        }
        strcat(name_with_spaces, name);
        strcpy(horse->name, name_with_spaces);
}

int main(int argc, char **argv) {
        int i;
        pthread_t threads[5];
        time_t t;

        won = -1;
        race_length = 25;

        srand((unsigned) time(&t));
        pthread_mutex_init(&print_mutex, NULL);

        get_horse_name(&horses[0]);
        get_horse_name(&horses[1]);
        get_horse_name(&horses[2]);
        get_horse_name(&horses[3]);
        get_horse_name(&horses[4]);
        horses[0].odds = rand() % 6 + 2;
        horses[1].odds = rand() % 6 + 2;
        horses[2].odds = rand() % 6 + 2;
        horses[3].odds = rand() % 6 + 2;
        horses[4].odds = rand() % 6 + 2;


        initscr();
        printscr(-1);
        for (i = 0; i < 5; i++) {
                int *arg = malloc(sizeof(*arg));
                *arg = i;
                pthread_create(&threads[i], NULL, horse, arg);
        }
        for (i = 0; i < 5; i++) {
                pthread_join(threads[i], NULL);
        }
        endwin();
        pthread_mutex_destroy(&print_mutex);

        return 0;
}
