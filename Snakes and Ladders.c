#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#define MAX 8
int p_pos[8] = {0}, p_count, dice, snake_start[5] = {98, 83, 76, 45, 20}, snake_end[5] = {67, 51, 23, 29, 3}, ladder_start[5] = {8, 13, 37, 69, 48};
int mode, ladder_end[5] = {28, 64, 55, 89, 75}, players;
char P[8][20];
void end_game();
void board()
{
	int i, k, j, check = false;
	for (k = 10; k>=1;)
	{
		for (i = k*10; i >= (k*10)-9 ; i--) 
		{
			for(j = 0; j<= MAX; j++)
			{
				if(p_pos[j] == i)
				{
					printf("Pl%d\t", j + 1);
					check = true;
					break;
				}
			}
			if(!check)
			{
				printf("%d\t", i);
			}
			check = false;
		}
		k--;
		printf("\n");
		for (i = (k*10)-9; i <= k*10; i++)
		{
			for(j = 0; j<= MAX; j++)
			{
				if(p_pos[j] == i)
				{
					printf("Pl%d\t", j + 1);
					check = true;
					break;
				}
			}
			if(!check)
			{
				printf("%d\t", i);
			}
			check = false;
		}
		k--;
		printf("\n");
	}
}
void Dice()
{
	srand((unsigned)time(0));
	dice = (rand()%6+1);
}
int player_position(int j)
{
	int i;
	if(p_pos[j] == 0)
	{	
		if(dice == 6)
		{
			p_pos[j] = 1;
			return j;
		}else 
		{
			return (j + 1)%players;
		}
	}else if(p_pos[j] != 0 && (p_pos[j] + dice) <= 100)
	{
		p_pos[j] = p_pos[j] + dice;
		for(i = 0; i< 5; i++)
		{
			if(p_pos[j] == snake_start[i])
			{
				p_pos[j] = snake_end[i];
				printf("\aOOPS! You stepped on a snake.\n");
			}
			if(p_pos[j] == ladder_start[i])
			{
				p_pos[j] = ladder_end[i];
				printf("\aCONGRATULATIONS! You stepped on a ladder.\n");
			}
		}
		if(p_pos[j] == p_pos[(j + 1)%players])
		{
			p_pos[(j + 1)%players] = 0;
			printf("\aPlayer %d has been knocked out.\n", (j + 1)%players + 1);
		}
		if(p_pos[j] == 100)
		{
			if(mode == 1 && p_pos[1] == 100)
			{
				printf("You have lost the game!.\n");
				return 9;
			}else
			{
				printf("Congratulations! %s has won the game.\n", P[j]);
				return 9;
			}
		}
		if(dice != 6)
		{
			return (j + 1)%players;
		}
		if (dice ==6)
		{
			return j;
		}
	}
}
void game(){
	int turn = 0;
	while(turn != 9){
		int i;
		board();
		Dice();
		turn = player_position(turn);
		printf("Dice roll = %d. \n", dice);
		for(i = 0; i<players; i++){
			if(mode == 1 && i == 1){
				printf("Computer position: %d.\n", p_pos[1]);
			}else{
				printf("Player %s position: %d.\n", P[i], p_pos[i]);
			}
		}
		sleep(1);
		if((mode == 1 && turn == 0) || mode == 0){
			getchar();
		}
	}
}
void start_menu()
{
	int i;
	mode = 0;
	printf("Select the number of players you want.\nMaximum players allowed = 8.\n");
	scanf(" %d", &players);
	gets(P[0]);
	if(players < 1)
	{
		printf("Invalid input!");
	}else if(players > 8)
	{
		printf("Too many Players!");
	}else if(players == 1)
	{
		printf("Enter the name of player: ");
		gets(P[0]);
		printf("\n");
		mode = 1;
		players = 2; 
	}else if(players <= 8)
	{
		for(i = 0; i < players; i++)
		{
			printf("Enter the name of player %d: ", i+1);
			gets(P[i]);
			printf("\n");
		}
	}
}
void end_game()
{
	int decision;
	printf("Press 1 to end game.\n Press 2 to start over.\n");
	scanf("%d", &decision);
	while (1)
	{
		if(decision == 1)
		{
			printf("Game Over!");
			break;
		}else if (decision == 2){
			main();
		}
	}
}
int main()
{
	printf("Welcome to snakes and ladders.\n");
	start_menu();
	game();
	end_game();
	return 0;
}
