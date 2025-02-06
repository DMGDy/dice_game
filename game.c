#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int number;
  int score;
}user_t;

void clear_input_buffer(void);
int get_choice(void);
void roll_dice(unsigned int [2],user_t*);

void
clear_input_buffer(void) {
  int c;
  while((c = getchar() != '\n' && c != EOF));
}

int
get_choice(void) {
  char buff[1] = {0};
  read(STDIN_FILENO,buff,1); 
  clear_input_buffer();
  return atoi(buff);
}

void
roll_dice(unsigned int dice_seed[2],user_t* user) {
  printf("User %d, which die would you like to use? (1 or 2):\n",user->number);

  int die_num = get_choice();
  srand(dice_seed[die_num]+time(NULL));

  int roll = rand()%6;
  roll += (roll == 0)? 1: 0;

  printf("The value from Die %d is: %d\n", die_num, roll);
  user->score += roll;
}

int
main(void) {
  unsigned int rseed1 = time(NULL);
  unsigned int rseed2 = rseed1 + rand();

  unsigned int dice_seed[2] = {rseed1, rseed2};

  user_t user1 = {
    .number = 1,
    .score = 0
  };

  user_t user2 = {
    .number = 2,
    .score = 0
  };

  printf("Do you want to play the game? 1 (yes) or 0 (no):\n");
  int choice = get_choice();

  while(choice) {
    printf("Current Score, User 1: %d & User 2: %d\n",user1.score,user2.score);

    roll_dice(dice_seed,&user1);
    printf("Added to User 1 score, Current score: %d\n",user1.score);

    roll_dice(dice_seed,&user2);
    printf("Added to User 2 score, Current score: %d\n",user2.score);

    printf("Do you want to continue playing the game? 1 (yes) or 0 (no):\n");
    choice = get_choice();
  }

  printf("User 1 Score: %d\nUser 2 Score: %d\n",user1.score,user2.score);
  if(user1.score == user2.score) {
    printf("It was a tie! No winners.\n");
  } else if(user1.score > user2.score) {
    printf("User 1 wins!\n");
  }else{
    printf("User 2 wins!\n");
  }

  return 0;
}
