#include "booleansInC.h"

typedef struct Player player;
typedef struct Monster monster;
struct Player
{
    char *Name;
    int HitsPoints;
    int Attack;
    int Defense;
    int roundPoisoned;
    int roundStunned;
    int roundSilenced;
    int roundBlinded;

    char *booleans;
    void (*print)(player *);
    char *(*classprinter)(player *);
    void (*atMonst)(player *, monster *);

    void (*helPlay)(player *, int);
    player *(*createPlay)(char *);
};

struct Monster
{
    int ID;
    int HitsPoints;
    int Attack;
    int DefenseScore;
    int numberOfAttacks;
    int numberOfLandedHits;

    monster *(*createMonst)();
    void (*print)(monster *);
    int (*atPlay)(player *, monster *);
};
int roundNo;
int playersLeft;
int numberOfMonsts;
int theAttacked;
int j;
/*Monster methods*/
monster *newMonster();
void printMonsterInformation(monster *m);
int attackPlayer(player *p, monster *m);
void deleteMonster(int x);
/*Player methods*/
player *newPlayer(char *name);
void printPlayerInformation(player *p);
char *print_class(player *p);
void attackMonster(player *p, monster *m);
void deletePlayer(int x);
void healPlayer(player *p, int x);

player **players;
monster **monsters;

player *newPlayer(char *name)
{
    player *result;
    char StatChar;
    char *pStatChar;
    int classDecimalNumber;
    int updateValue;
    int i;

    result = (player *)malloc(sizeof(player));

    result->Name = (char *)malloc(strlen(name) * sizeof(char) + 1);
    strcpy(result->Name, name);

    result->HitsPoints = 100;
    result->Attack = 100;
    result->Defense = 100;
    StatChar = (char)(lottery_int(0, 127));
    pStatChar = &StatChar;

    result->booleans = (char *)malloc(1 * sizeof(char) + 1);
    strcpy(result->booleans, pStatChar);
    classDecimalNumber = (get_boolean_value(result->booleans, 2)) * 4 + (get_boolean_value(result->booleans, 1)) * 2 + (get_boolean_value(result->booleans, 0));
    updateValue = (classDecimalNumber % 2) ? 1 : 0;
    update_boolean_value(result->booleans, 3, updateValue);
    for (i = 4; i <= 7; i++)
    {
        update_boolean_value(result->booleans, i, 0);
    }

    result->roundPoisoned = 0;
    result->roundStunned = 0;
    result->roundSilenced = 0;
    result->roundBlinded = 0;

    result->print = printPlayerInformation;
    result->classprinter = print_class;
    result->atMonst = attackMonster;

    result->helPlay = healPlayer;
    result->createPlay = newPlayer;

    return result;
}

void printPlayerInformation(player *p)

{
    /*char arr[8][10] = {"Paladin", "Barbarian", "Druid", "Monk", "Priest", "Rogue", "Mage", "Warrior"};*/

    /*
    index 7. Poison (Yes/No) Yes is 1. No is 0.
    6. Stun (Yes/No)
    5. Silent (Yes/No)
    4. Blinded (Yes/No)
    3. Physical/Magical attacker (1/0)
    2,1,0. Class

    the decimal numbers that make up the 0th,1st and 2nd bits are decimal numbers 0 to 7
    index 3 and 0 must be the same
    physical attacker must be encoded in odd numbers, magical attacker in even numbers


    7. Warrior (physical attacker)
    5. Rogue (physical attacker)
    6. Mage (magical attacker)
    4. Priest (magical attacker)
    2. Druid (magical attacker)
    3. Monk (physical attacker)
    0. Paladin (magical attacker)
    1. Barbarian (physical attacker)


    */
    printf("\n");
    printf("Name: %s\n HP:%d\n Attack:%d\n Defense:%d\n", p->Name, p->HitsPoints,
           p->Attack, p->Defense);
    printf("Poison: %d\n", (get_boolean_value(p->booleans, 7)));
    printf("Stun: %d\n", (get_boolean_value(p->booleans, 6)));
    printf("Silent: %d\n", (get_boolean_value(p->booleans, 5)));
    printf("Blinded: %d\n", (get_boolean_value(p->booleans, 4)));
    printf("Physical/Magical attacker: %s\n", ((get_boolean_value(p->booleans, 3)) ? "Physical" : "Magical"));
    printf("Class: %s\n", p->classprinter(p));
    printf("\n");
}

char *print_class(player *p)
{
    int classDecimalNumber;
    char *classWord;

    classDecimalNumber = get_boolean_value(p->booleans, 2) * 4 + get_boolean_value(p->booleans, 1) * 2 + get_boolean_value(p->booleans, 0);
    switch (classDecimalNumber)
    {

    case 0:
        classWord = "Paladin";

        break;
    case 1:
        classWord = "Barbarian";

        break;
    case 2:
        classWord = "Druid";

        break;
    case 3:
        classWord = "Monk";

        break;
    case 4:
        classWord = "Priest";

        break;
    case 5:
        classWord = "Rogue";

        break;
    case 6:
        classWord = "Mage";

        break;
    case 7:
        classWord = "Warrior";

        break;
    }
    return classWord;
}

void healPlayer(player *p, int roundNo)
{
    if (get_boolean_value(p->booleans, 7) == 1)
    {
        if (roundNo - p->roundPoisoned == 3)
        {
            update_boolean_value(p->booleans, 7, 0);
            printf("Poison ailment inflicted on round %d has expired on %s.\n", p->roundPoisoned, p->Name);
            p->roundPoisoned = 0;
        }
    }
    else if (get_boolean_value(p->booleans, 6) == 1)
    {
        if (roundNo - p->roundStunned == 3)
        {
            update_boolean_value(p->booleans, 6, 0);
            printf("Stun ailment inflicted on round %d has expired on %s.\n", p->roundStunned, p->Name);
            p->roundStunned = 0;
        }
    }
    else if (get_boolean_value(p->booleans, 5) == 1)
    {
        if (roundNo - p->roundSilenced == 3)
        {
            update_boolean_value(p->booleans, 5, 0);

            printf("Silence ailment inflicted on round %d has expired on %s.\n", p->roundSilenced, p->Name);
            p->roundSilenced = 0;
        }
    }
    else if (get_boolean_value(p->booleans, 4) == 1)
    {
        if (roundNo - p->roundBlinded == 3)
        {
            update_boolean_value(p->booleans, 4, 0);

            printf("Blind ailment inflicted on round %d has expired on %s.\n", p->roundBlinded, p->Name);
            p->roundBlinded = 0;
        }
    }
}

void deletePlayer(int x)
{

    if (players[x]->HitsPoints <= 0)
    {
        printf("Player %s has died.\n", players[x]->Name);
        free(players[x]->Name);
        free(players[x]->booleans);
        free(players[x]);

        for (j = x; j < playersLeft; j++)
        {
            players[j] = players[j + 1];
        }
        players[playersLeft - 1] = NULL;
        playersLeft -= 1;
        if (playersLeft == 0)
        {
            printf("Oh no, all our players died. RIP Players! The Monsters have won.\n");
        }
        else
        {
            printf("The following players mourn the loss of their friend.\n");
            for (x = 0; x < playersLeft; x++)
            {
                players[x]->print(players[x]);
            }
            printf("They will avenge their friend.\n");
        }
    }
}

void attackMonster(player *p, monster *m)

{
    int damage;
    printf("Player %s is going to attack Monster %d.\n", p->Name, m->ID);

    damage = p->Attack + (lottery_int(1, 10)) - m->DefenseScore;
    /*Player can only fight if they are not stunned*/
    if (get_boolean_value(p->booleans, 6) == 0)
    {
        /*if player is a physical attacker*/
        if (get_boolean_value(p->booleans, 3))
        {
            /*If player is blinded*/
            if (get_boolean_value(p->booleans, 4) == 1)
            {
                printf("Player %s is a physical attacker who is blinded. Chances of making a hit are halved.\n", p->Name);

                if (rand() % 2 == 0)
                {
                    m->HitsPoints -= damage;
                    printf("Monster  %d was hit. Damage done is %d. Now the HP of Monster %d is %d. \n", m->ID, damage, m->ID, m->HitsPoints);
                    deleteMonster(theAttacked);
                }
                else
                {

                    printf("No damage done to Monster %d.\n", m->ID);
                }
            }
            /*else Player is just fine*/
            else
            {
                m->HitsPoints -= damage;
                printf("Monster  %d was hit. Damage done is %d. Now the HP of Monster %d is %d. \n", m->ID, damage, m->ID, m->HitsPoints);
                deleteMonster(theAttacked);
            }
        }
        /*else player is magical attacker */
        else
        {
            /*if player is silenced*/
            if (get_boolean_value(p->booleans, 5) == 1)
            {
                printf("Player %s is a magical attacker who is silenced. Chances of making a hit are halved.\n", p->Name);

                if (rand() % 2 == 0)
                {
                    m->HitsPoints -= damage;
                    printf("Monster  %d was hit. Damage done is %d. Now the HP of Monster %d is %d. \n", m->ID, damage, m->ID, m->HitsPoints);
                    deleteMonster(theAttacked);
                }
                else
                {
                    printf("No damage done to Monster %d.\n", m->ID);
                }
            }
            /*else Player is just fine*/
            else
            {
                m->HitsPoints -= damage;
                printf("Monster  %d was hit. Damage done is %d. Now the HP of Monster %d is %d. \n", m->ID, damage, m->ID, m->HitsPoints);
                deleteMonster(theAttacked);
            }
        }
    }
    else
    {
        printf("Player %s is unable to attack because they are stunned.\n", p->Name);
    }
}

monster *newMonster()
{
    monster *result;

    result = (monster *)malloc(sizeof(monster));
    result->HitsPoints = 100;
    result->Attack = 100;
    result->DefenseScore = 100;
    result->numberOfAttacks = 0;

    result->ID = rand();
    result->createMonst = newMonster;
    result->print = printMonsterInformation;
    result->atPlay = attackPlayer;

    return result;
}

void printMonsterInformation(monster *m)
{
    printf("\n");
    printf("ID: %d\n", m->ID);
    printf("HitPoints: %d\n", m->HitsPoints);
    printf("Attack: %d\n", m->Attack);
    printf("DefenseScore: %d\n", m->DefenseScore);
    printf("\n");
}

int attackPlayer(player *p, monster *m)

{
    int damage;

    printf("Monster %d is going to attack Player %s.\n", m->ID, p->Name);
    m->numberOfAttacks += 1;

    /*missed*/
    if ((m->numberOfAttacks % 4) == 0)
    {
        printf("Hit missed.\n");
        return 0;
    }
    else
    {
        printf("Hit landed.\n");
        damage = m->Attack + lottery_int(1, 5) - p->Defense;
        m->numberOfLandedHits += 1;

        /*did not miss*/
        /*25% chance of applying one of the random stats ailments*/
        if ((m->numberOfLandedHits % 4) == 0)
        {
            /*random chance of applying each status ailment*/
            if ((rand() % 4) == 0)
            {
                update_boolean_value(p->booleans, 7, 1);
                damage = damage + ((int)((damage / 4) * 3));

                printf("Player %s is poisoned.\n", p->Name);
                p->roundPoisoned = roundNo;
            }
            else if ((rand() % 4) == 1)
            {
                update_boolean_value(p->booleans, 6, 1);
                printf("Player %s is stunned.\n", p->Name);
                p->roundStunned = roundNo;
            }
            else if ((rand() % 4) == 2)
            {
                update_boolean_value(p->booleans, 5, 1);
                printf("Player %s is silenced.\n", p->Name);
                p->roundSilenced = roundNo;
            }
            else
            {
                update_boolean_value(p->booleans, 4, 1);
                printf("Player %s is blinded.\n", p->Name);
                p->roundBlinded = roundNo;
            }
        }
        else
        {
            printf("No status ailments inflicted on %s.\n", p->Name);
        }
        p->HitsPoints -= damage;
        printf("Damage done is %d. Now the HP of %s is %d. \n", damage, p->Name, p->HitsPoints);
        deletePlayer(theAttacked);
        return 1;
    }
}

void deleteMonster(int x)
{
    if (monsters[x]->HitsPoints <= 0)
    {
        printf("Monster %d has died.\n", monsters[x]->ID);

        free(monsters[x]);

        for (j = x; j < numberOfMonsts; j++)
        {
            monsters[j] = monsters[j + 1];
        }
        monsters[numberOfMonsts - 1] = NULL;
        numberOfMonsts -= 1;

        printf("Which are the monsters are there left to die ?!\n ");
        if (numberOfMonsts == 0)
        {
            printf("All monsters are dead! Our players have won!\n");
        }
        else
        {
            printf("Who are the other monsters to kill?!");
            for (x = 0; x < numberOfMonsts; x++)
            {
                monsters[x]->print(monsters[x]);
            }
            printf("Our players will kill them all");
        }
    }
}
