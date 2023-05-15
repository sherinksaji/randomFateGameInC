#include "player.h"
#include <time.h>
int main(int argc, char **argv)
{
    /*char c = 'b';
    char *booleans = &c;
    print_all_boolean(booleans);
    update_boolean_value(booleans, 1, 0);
    print_all_boolean(booleans);

    printf("%d", get_boolean_value(booleans, 7));
    printf("%d", get_boolean_value(booleans, 6));

    printf("%d", get_boolean_value(booleans, 5));
    printf("%d", get_boolean_value(booleans, 4));
    printf("%d", get_boolean_value(booleans, 3));
    printf("%d", get_boolean_value(booleans, 2));
    printf("%d", get_boolean_value(booleans, 1));
    printf("%d", get_boolean_value(booleans, 0));

    return 0;
    */
    player *first;
    player *second;
    player *third;
    player *fourth;

    int i;

    srand(time(NULL));
    first = newPlayer("Tiger");
    second = newPlayer("Balu");
    third = newPlayer("Tarzan");
    fourth = newPlayer("Jane");

    players = (player **)malloc(sizeof(player *) * 4);
    players[0] = first;
    players[1] = second;
    players[2] = third;
    players[3] = fourth;

    numberOfMonsts = lottery_int(1, 6);
    monsters = (monster **)malloc(sizeof(monster *) * numberOfMonsts);
    for (i = 0; i < numberOfMonsts; i++)
    {
        monsters[i] = newMonster();
    }
    printf("Try 1");
    printf("The following are the players in this game.\n");
    for (i = 0; i < 4; i++)
    {
        players[i]->print(players[i]);
    }

    printf("There are %d monsters in this game.\n", numberOfMonsts);

    for (i = 0; i < numberOfMonsts; i++)
    {
        monsters[i]->print(monsters[i]);
    }

    /*players[0]->HitsPoints = 4;

    playersLeft = 4;
    theAttacked = 0;
    printf("----ROUND 1-----");
    round = 1;
    players[0]->print(players[0]);
    monsters[0]->atPlay(players[0], monsters[0]);
    players[0]->print(players[0]);

    printf("----ROUND 2-----");
    round++;
    players[0]->helPlay(players[0], 2);
    players[0]->print(players[0]);
    monsters[0]->atPlay(players[0], monsters[0]);
    players[0]->print(players[0]);

    printf("----ROUND 3-----");
    round++;
    players[0]->helPlay(players[0], 3);
    players[0]->print(players[0]);
    monsters[0]->atPlay(players[0], monsters[0]);
    players[0]->print(players[0]);

    printf("----ROUND 4-----");
    round++;
    players[0]->helPlay(players[0], 4);
    players[0]->print(players[0]);
    monsters[0]->atPlay(players[0], monsters[0]);
    players[0]->print(players[0]);
    deletePlayer(players, 0);
    printf("----ROUND 5-----");
    round++;
    players[0]->helPlay(players[0], 5);
    players[0]->print(players[0]);
    monsters[0]->atPlay(players[0], monsters[0]);
    players[0]->print(players[0]);
    deletePlayer(players, 0);*/

    /*for (i = 0; i <= 3; i++)
    {
        players[i]->print(players[i]);
    }
    printf("There are %d monsters in this game.\n", numberOfMonsts);
    for (i = 0; i < numberOfMonsts; i++)
    {
        monsters[i]->print(monsters[i]);
    }*/

    roundNo = 0;
    playersLeft = 4;
    do
    {
        roundNo++;
        printf("----------ROUND %d------------ \n", roundNo);
        /*heal players*/
        printf("\nHealing ...\n");
        for (i = 0; i < playersLeft; i++)
        {

            players[i]->helPlay(players[i], roundNo);
        }
        printf("\nHealing Over.\n");

        printf("\nPlayers are going to attack...\n");
        /*players attack*/

        for (i = 0; i < playersLeft; i++)
        {
            theAttacked = lottery_int(0, numberOfMonsts - 1);

            players[i]->atMonst(players[i], monsters[theAttacked]);

            if (numberOfMonsts == 0)
            {

                return 0;
            }
        }

        printf("\nPlayers attacks are over.\n");

        printf("\nMonsters are going to attack...\n");

        /*monsters attack*/
        printf("passed here.\n");
        for (i = 0; i < numberOfMonsts; i++)

        {

            theAttacked = lottery_int(0, playersLeft - 1);
            monsters[i]->atPlay(players[theAttacked], monsters[i]);

            if (playersLeft == 0)
            {

                return 0;
            }
        }
        printf("\nMonsters attacks are over...\n");

        printf("\nnumberOfMOnsts=%d,playersLeft=%d\n", numberOfMonsts, playersLeft);
    } while (1);

    free(players);
    free(monsters);

    return 0;
}
