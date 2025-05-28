/*
 * Copyright (c) 2025 Rithwik A. Agarwal
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This file is part of the "Stone-Paper-Scissors Game" project.
 * See the LICENSE file for the full license text.
 */

/** 
 * File: Stone-Paper-Scissors.c
 * Author: Rithwik A. Agarwal
 * Date: May 10, 2025
 * Description: Implements a command-line Stone-Paper-Scissors game against a computer.
 * Features ASCII art display for moves, a 'best-of' series format,
 * and robust input handling.
 * Dependencies:
 * - Requires the 'figlet' utility to be installed and accessible in the system's PATH
 * for displaying the final win/loss message.
 * - Designed for Unix-like operating systems (Linux, macOS, BSD) due to the use
 * of POSIX-specific functions like fork(), execvp(), usleep(), and sys/wait.h.
 */

# define _DEFAULT_SOURCE    // Define _DEFAULT_SOURCE to expose POSIX and other common extensions.
# include <stdio.h> // Standard input/output functions (printf, putchar, fgets, scanf)      
# include <stdlib.h>    // Standard library functions (srand, rand, exit, _exit)    
# include <string.h>    // String manipulation functions (strlen, strcmp)
# include <time.h>  // Time functions (time) for seeding random number generator
# include <unistd.h>    // POSIX operating system API (usleep, fork, execvp, _exit)
# include <ctype.h> // Character handling functions (tolower)
# include <sys/wait.h>  // POSIX functions for child processes (waitpid, WIFEXITED, WEXITSTATUS)

// Function prototypes
/**
 * @brief Prints three ASCII arts side-by-side to the console.
 *
 * This function iterates through each line of the provided ASCII art arrays
 * and prints them sequentially on the same console line, followed by a newline.
 * A short delay is introduced after printing each line to create a retro-like
 * visual effect as the art appears.
 *
 * @param art1 Pointer to the first ASCII art array (array of strings).
 * @param art2 Pointer to the second ASCII art array (array of strings).
 * @param art3 Pointer to the third ASCII art array (array of strings).
 * @param height The number of lines (rows) in each ASCII art.
 * @note Uses usleep for delays, which is POSIX-specific.
 */
void asciiArtPrinter(const char **art1, const char **art2, const char **art3, int height);

/**
 * @brief Generates a random integer within a specified range (inclusive).
 *
 * This function uses the rand() function (seeded by srand in main)
 * to produce a random number within the desired min and max limits.
 *
 * @param min The minimum value for the random number (inclusive).
 * @param max The maximum value for the random number (inclusive).
 * @return A random integer between min and max (inclusive).
 */
int randomNumber(int min, int max);

/**
 * @brief Prompts the player for their choice (Stone, Paper, or Scissors) and validates it.
 *
 * This function attempts to read valid input for up to MAX_CHOICE_ATTEMPTS times.
 * It converts the input to lowercase for case-insensitive comparison and clears
 * the input buffer after reading. If valid input is received, it returns a
 * corresponding integer. If attempts are exhausted, the program exits.
 *
 * @return An integer representing the player's choice:
 * 1 for "Stone"
 * 2 for "Paper"
 * 3 for "Scissors"
 * @note This function will terminate the program if too many invalid inputs are provided.
 */
int getPlayerChoice();

/**
 * @brief Clears any remaining characters in the standard input buffer up to a newline or EOF.
 *
 * This function is crucial after using scanf or fgets (when fgets doesn't
 * consume all input), to ensure that leftover characters (like newlines) don't
 * interfere with subsequent input operations. It reads and discards characters
 * until a newline character or the end of the input stream (EOF) is encountered.
 */
void clearInputBuffer();

// Define constants for various configurable aspects of the game
#define ART_HEIGHT 20   // Height of each ASCII art in lines.
#define COMBINED_ART_WIDTH "180"    // Maximum width of figlet output to make it consistent with the width of the 3 arts side-by-side.
#define MAX_PLAYER_NAME 20  // Maximum characters allowed for the player's name (including null terminator).
#define MAX_CHOICE_ATTEMPTS 5   // Maximum attempts a player has to enter a valid Stone/Paper/Scissors choice.
#define MAX_WIN_MESSAGE_BUFFER 120  // Buffer size for the final win/loss message string passed to figlet.
#define MAX_CHOICE_INPUT_LENGTH 9   // Max characters for player's choice input (e.g., "Scissors" is 7 chars + newline + null).
// Delays to produce retro-like display effect
#define UI_MICRO_DELAY_SHORT 100000 // Short delay (100 milliseconds).
#define UI_MICRO_DELAY_MEDIUM 200000    // Medium delay (200 milliseconds).
#define UI_MICRO_DELAY_LONG 500000  // Long delay (500 milliseconds).

int main() {

    // Seed the random number generator with the current date and time.
    // This ensures different random numbers each time the program runs.
    srand(time(NULL));

    // Define ASCII art for Stone, Paper, Scissors, and the 'VS' separator.
    // These are arrays of strings, where each string represents a line of the art.

const char *stone[] = {
        "                                                            ",
        "                                                            ",
        "                                                            ",
        "                        ...'..                              ",
        "                ...,;cloooolodddl:,..                       ",
        "          .::clllooooooooooollllllooddddl:,'.               ",
        "         :lllllllooooooooddoolllllllllldxxxxxxl'            ",
        "        ,;::cllllooooooooddddddlllllllllldxxxxxxd:          ",
        "       .,,,,,,,:clodoooooddddddddollllllllxxxxxxxxxc.       ",
        "        ,,,,,,,,,,,,;::clddddddddddddooolloxxxxxxxxx:       ",
        "        .,,,,,,,,,,,,,,,,,:clodddddddxxxxdoodxxxxxx:        ",
        "        ,;;;,,,,,,,,,,,,,,,,,,,;:ccdxxxxxxxxxddlol.         ",
        "       .;;;;;;;;;;;,,,,,,,,,,,;;;,,::::::;,,'''             ",
        "       .;;;;;;;;;;;;;;:;;;,,,,''''''''''''''                ",
        "           ';;;;;;;,,,'''''''''''''''''''.                  ",
        "                         .''''''''''''.                     ",
        "                                                            ",
        "                                                            ",
        "                                                            ",
        "                                                            "};
        
    const char *paper[] = {
        "                                                            ",
        "           ...........................                      ",
        "           'okkkkkkkkkkk         ;l,  '.                    ",
        "           'd000000000          .ll;.   ...                 ",
        "           'd0000000o            ll''      '.               ",
        "           'd000000k             ;l''......''''             ",
        "           'd000000.                 lllc    ..             ",
        "           'd000000                          '.             ",
        "           'd000000                                         ",
        "           'd000000                          .              ",
        "           'd000000'                                        ",
        "           'd000000O                                        ",
        "           'd0000000k                        '.             ",
        "           'd00000000k.                      '.             ",
        "           'd0000000000l                     '.             ",
        "           'd000000000000o,                  '.             ",
        "           'd00000000000000Oc.               '.             ",
        "           'd00000000000000000x;             '.             ",
        "           ;;:::::::::::::::::::;'..........''.             ",
        "                                                            "};

    const char *scissors[] = {
        "                                                            ",
        "             .,c:.                        ,x:'.             ",
        "            .:odOkc.                    ;kxcxKc.            ",
        "            .codOkldl.               .;kxcxKKKl             ",
        "              :oxkkl:ol'           .:kxcxKKKO,              ",
        "                .oxkklcxo'       .:Ox:xKKKO,                ",
        "                  :oxkkoxko,.  .:OxcxKKKO,                  ",
        "                    'odkOOOOd,'OxcxKKKO'                    ",
        "                      'ldkOOOOd;;0KKk.                      ",
        "                        .ldx:::cd:l'                        ",
        "                       .'c;c;;:ckOd'.                       ",
        "                    .':ooc:',cddl:cooc'.                    ",
        "               ..,:loddddddo;  ,coddddddl:,'..              ",
        "           .,colc. cldddddc      ;codddl'  'lol;.           ",
        "          'ld;        'od:.      .,cc,        'oo'          ",
        "         .cd;          ,dl.      .:c,          ,dl.         ",
        "          ;dl.        .cdc        ,c:.        .cd;          ",
        "           .loc,....':oo,          .:c:,....,col.           ",
        "               .cllc.                   ;cc:                ",
        "                                                            "};

    const char *vs[] = {
        "                                                            ",
        "                     :dkKXWMMMMWXKkd:                       ",
        "                .lxOXWMMMMMMMMMMMMMMM,                      ",
        "             ;xKMMMMMMMMMMMMMMMMMMMM'                       ",
        "          .dXMMMMMMMMMMMMMMMMMMMMMM' d                      ",
        "         xWMMMMMMMMMMMMMMMMMMMMMMM. xl                      ",
        "       ,NMMMMMMMMMMMMMMMMMMMMMMMM. kN .'                    ",
        "      ;WMMMMMMMMMd    dMMMM0      kMl.O .                   ",
        "     .WMMMMMMMMMM0    'MMMO      OMM:doo:;                  ",
        "     kMMMMMMMMMMMW     WMO      OMMMMo,KMMMM;               ",
        "     WMMMMMMMMMMMM.    OO      kMMMMN                       ",
        "     KMMMMMMMMMMMMl    '       .dNMMMMNd'                   ",
        "     ,MMMMMMMMMMMMO                kMMMMM;                  ",
        "      kMMMMMMMMMMMWOoolO    0MMMM; oMMMMl                   ",
        "       xMMMMMMMMMMMXN'Xo   .d0XNNO0XKko.                    ",
        "        .MMMMMMMMMMM0NW                                     ",
        "          ,MMMMMMMMMMMo                                     ",
        "             XMMMMMMMN                                      ",
        "                ;MMMW                                       ",
        "                                                            "};

    char playerName[MAX_PLAYER_NAME];   // Buffer to store the player's name
    int bestOf; // Variable to store the number of total rounds                        

    usleep(UI_MICRO_DELAY_SHORT);   // Produce short delay 
    putchar('\n');
    printf("Player name: ");    // Prompt for player's name
    usleep(UI_MICRO_DELAY_SHORT);   

    // Read player name, ensuring it doesn't overflow the buffer.
    fgets(playerName, MAX_PLAYER_NAME, stdin);
    usleep(UI_MICRO_DELAY_SHORT);    

    size_t len = strlen(playerName);    // Get the length of player input to tackle corner cases

    // Remove the trailing newline character that fgets often captures.
    // If the input was too long for the buffer, clear the remaining characters.
    if ((len > 0) && (playerName[len - 1] == '\n')) 
        playerName[len - 1] = '\0';
    
    else
        clearInputBuffer(); // Clear remaining characters if input was too long

    putchar('\n');  // Print a newline for formatting
    usleep(UI_MICRO_DELAY_SHORT);             
    printf("Best of: ");    // Prompt for number of rounds
    usleep(UI_MICRO_DELAY_SHORT);

    // Collect the input for the bestOf variable.
    // scanResult checks if scanf successfully read an integer.
    int scanResult = scanf("%i", &bestOf);      
    usleep(UI_MICRO_DELAY_SHORT);

    // Clear any remaining characters in the input buffer after scanf.
    // This prevents issues with subsequent fgets calls.
    clearInputBuffer();

    // Validate bestOf input: must be a valid integer.
    if (scanResult != 1) {
        printf("Invalid input...\n\n");
        return 1;}  // Exit if input is not an integer

    // Validate bestOf input: must be a positive odd integer.
    if ((bestOf % 2 == 0) || (bestOf < 0)) {
        putchar('\n');
        usleep(UI_MICRO_DELAY_SHORT);
        printf("Only positive odd integers are valid...\n\n");
        return 1;}  // Exit if invalid

    // Calculate 'n', the number of wins required to win the game.
    // Example: Best of 3 -> n = (3+1)/2 = 2 wins required.
    int n = (bestOf + 1) / 2;

    int playerWins = 0; // Counter for player's wins
    int computerWins = 0;   // Counter for computer's wins

    int playerChoice;   // Stores player's choice (1:Stone, 2:Paper, 3:Scissor)
    int computerChoice; // Stores computer's choice

    // Main game loop: continues as long as neither player nor computer has reached 'n' wins.
    while ((playerWins < n) && (computerWins < n)) {

        playerChoice = getPlayerChoice();   // Get player's choice
        computerChoice = randomNumber(1, 3);    // Generate computer's random choice (1-3)

        // Game logic to determine the winner of the round based on choices
        if (playerChoice == 1) {    // Player chose Stone
            
            if (computerChoice == 1) {  // Stone vs Stone = Tie
                asciiArtPrinter(stone, vs, stone, ART_HEIGHT);}
            
            else if (computerChoice == 2) { // Stone vs Paper = Computer Wins
                asciiArtPrinter(stone, vs, paper, ART_HEIGHT);
                computerWins++;}

            else {  // Stone vs Scissors = Player Wins
                asciiArtPrinter(stone, vs, scissors, ART_HEIGHT);
                playerWins++;}}
             
        else if (playerChoice == 2) {   // Player chose Paper
            
            if (computerChoice == 1) {  // Paper vs Stone = Player Wins
                asciiArtPrinter(paper, vs, stone, ART_HEIGHT);
                playerWins++;}
            
            else if (computerChoice == 2) { // Paper vs Paper = Tie
                asciiArtPrinter(paper, vs, paper, ART_HEIGHT);}

            else {  // Paper vs Scissors = Computer Wins
                asciiArtPrinter(paper, vs, scissors, ART_HEIGHT);
                computerWins++;}}
        
        else {  // Player chose Scissors
            
            if (computerChoice == 1) {  // Scissors vs Stone = Computer Wins     
                asciiArtPrinter(scissors, vs, stone, ART_HEIGHT);
                computerWins++;}
            
            else if (computerChoice == 2) { // Scissors vs Paper = Player Wins
                asciiArtPrinter(scissors, vs, paper, ART_HEIGHT);
                playerWins++;}

            else {  // Scissors vs Scissors = Tie
                asciiArtPrinter(scissors, vs, scissors, ART_HEIGHT);}}

        // After each round, check if the game has concluded or continues.
        if ((playerWins != n) && (computerWins != n)) { 
            putchar('\n');
            usleep(UI_MICRO_DELAY_SHORT);
            printf("%s : %i | Computer : %i", playerName, playerWins, computerWins);    // If the game is still ongoing, display current scores.
            usleep(UI_MICRO_DELAY_SHORT);
            putchar('\n');
            usleep(UI_MICRO_DELAY_SHORT);}

        // Game has concluded (either player or computer won the game).
        else {  

            char winMessage[MAX_WIN_MESSAGE_BUFFER];    // Buffer for the final win/loss message

            // Arguments for the figlet command: executable, width flag, width value, message, NULL terminator.
            char *figlet[5] = {"figlet", "-w", COMBINED_ART_WIDTH, winMessage, NULL};

            // Add pauses to simulate processing of scores before revealing the final result.
            putchar('\n');
            usleep(UI_MICRO_DELAY_MEDIUM);
            printf(".\n");
            usleep(UI_MICRO_DELAY_LONG);
            printf("..\n");
            usleep(UI_MICRO_DELAY_LONG);
            printf("...\n");
            usleep(UI_MICRO_DELAY_LONG);
            putchar('\n');
            usleep(UI_MICRO_DELAY_MEDIUM);

            // Format the final win message based on who won the game.
            if (playerWins == n) 
                snprintf(winMessage, MAX_WIN_MESSAGE_BUFFER, "%s  :  %i        |        Computer  :  %i\n%s   wins !", playerName, playerWins, computerWins, playerName);
            else
                snprintf(winMessage, MAX_WIN_MESSAGE_BUFFER, "%s  :  %i        |        Computer  :  %i\nComputer   wins !", playerName, playerWins, computerWins);

            // Fork a new process to execute the 'figlet' command.
            pid_t pid = fork();

            if (pid == -1) {
                // Handle fork failure.
                perror("Fork failed");
                return 1;} 
            
            else if (pid == 0) {
                // This is the child process. It will execute figlet.
                // execvp replaces the current process image with a new one (figlet).
                execvp(figlet[0], figlet);
                // If execvp returns, it means it failed to execute figlet.
                perror("Figlet execution failed");
                // Use _exit to terminate the child process immediately without flushing buffers
                // that might belong to the parent process or calling atexit handlers.
                _exit(1);}
            
            else {
                // This is the parent process.
                int status;
                waitpid(pid, &status, 0);   // Wait for child to exit

                // Check how the child process terminated.
                if (WIFEXITED(status) != 0) {
                    // Child terminated normally. Check its exit status.
                    if (WEXITSTATUS(status) != 0) {
                        // Child exited with a non-zero status, indicating an error in figlet.
                        fprintf(stderr, "Child process failed to execute with status %d\n", WEXITSTATUS(status));
                        return 1;}}

                else {
                    // Child process terminated abnormally (e.g., by a signal).
                    fprintf(stderr, "Child process terminated abnormally\n");
                    return 1;}}}}
                
    return 0;}  // Program completed successfully

void asciiArtPrinter(const char **art1, const char **art2, const char **art3, int height) {

    for(int i = 0; i < height; i++) {

        printf("%s%s%s\n", *art1, *art2, *art3); // Print line from first, second and third art side-by-side
        art1++; art2++; art3++; // Move the pointers to the next line in each art
        usleep(UI_MICRO_DELAY_SHORT);}}

int randomNumber(int min, int max) {

    int number;

    number = rand() % (max - min + 1) + min;

    return number;}

int getPlayerChoice() { 

    for(int i = 0; i < MAX_CHOICE_ATTEMPTS; i++) {
    
        char tempPlayerChoice[MAX_CHOICE_INPUT_LENGTH]; // Buffer for player's string input

        putchar('\n');
        usleep(UI_MICRO_DELAY_SHORT);
        printf("Stone, Paper or Scissors: ");
        usleep(UI_MICRO_DELAY_SHORT);
        fgets(tempPlayerChoice, MAX_CHOICE_INPUT_LENGTH, stdin);
        putchar('\n');
        usleep(UI_MICRO_DELAY_SHORT);

        size_t len = strlen(tempPlayerChoice);

        // Remove trailing newline or clear buffer if input exceeds buffer size.
        if ((len > 0) && (tempPlayerChoice[len - 1] == '\n')) 
            tempPlayerChoice[len - 1] = '\0';
        
        else 
            clearInputBuffer();
        
        // Convert the input string to lowercase for case-insensitive comparison.
        for (size_t i = 0; i < len; i++)    // Use size_t for loop counter 'i' to match 'len' (from strlen) and avoid -Wsign-compare warning.
            tempPlayerChoice[i] = tolower((unsigned char) tempPlayerChoice[i]);

        // Compare input string to valid choices.
        if (strcmp(tempPlayerChoice, "stone") == 0)
            return 1;

        else if (strcmp(tempPlayerChoice, "paper") == 0)
            return 2;

        else if (strcmp(tempPlayerChoice, "scissors") == 0)
            return 3;
        
        else {
            // Invalid input, prompt again.
            printf("Invalid Choice...\n");
            usleep(UI_MICRO_DELAY_SHORT);}}

    // If loop exits, it means max attempts were exceeded.
    printf("Too many invalid inputs...\n");
    exit(1);}   // Terminate program with error status

void clearInputBuffer(){
    int a;
    while (((a = getchar()) != '\n') && (a != EOF));}