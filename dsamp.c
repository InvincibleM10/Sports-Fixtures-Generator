#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEAMS 50
#define MAX_VENUES 10
#define MAX_MATCHES_PER_DAY 16

typedef struct {
    char name[50];
} Team;

typedef struct {
    char name[50];
} Venue;

typedef struct {
    char team1[50];
    char team2[50];
    char venue[50];
    char time[10];
} Match;

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Function to get user input for team names using fgets()
void getTeams(Team *teams, int numTeams) {
    printf("Enter names of %d teams:\n", numTeams);
    for (int i = 0; i < numTeams; i++) {
        printf("Team %d: ", i + 1);
        fgets(teams[i].name, sizeof(teams[i].name), stdin);
        teams[i].name[strcspn(teams[i].name, "\n")] = 0; // Remove trailing newline
    }
}

// Function to get user input for venue names using fgets()
void getVenues(Venue *venues, int numVenues) {
    printf("Enter names of %d venues:\n", numVenues);
    for (int i = 0; i < numVenues; i++) {
        printf("Venue %d: ", i + 1);
        fgets(venues[i].name, sizeof(venues[i].name), stdin);
        venues[i].name[strcspn(venues[i].name, "\n")] = 0; // Remove trailing newline
    }
}

// Function to generate fixtures for one round
void generateFixtures(Team teams[], int numTeams, Venue venues[], int numVenues, Match *matches, int matchLength) {
    if (numTeams % 2 != 0) {
        printf("Odd number of teams detected. Adding a 'BYE' team.\n");
        strcpy(teams[numTeams].name, "BYE");
        numTeams++;
    }

    int matchesPerRound = numTeams / 2;

    int matchIndex = 0;
    int hour = 9, minute = 0;

    printf("\nFixtures for Round 1:\n");
    for (int match = 0; match < matchesPerRound; match++) {
        int team1 = match;
        int team2 = numTeams - 1 - match;

        if (match == 0) {
            team2 = numTeams - 1; // Last team stays fixed
        }

        // Assign venue sequentially to ensure parallel matches are in different venues
        int venueIndex = match % numVenues;
        strcpy(matches[matchIndex].team1, teams[team1].name);
        strcpy(matches[matchIndex].team2, teams[team2].name);
        strcpy(matches[matchIndex].venue, venues[venueIndex].name);

        // Assign time slot
        if (hour == 13 && minute == 0) { // Skip lunch break
            hour = 14;
            minute = 0;
        }

        sprintf(matches[matchIndex].time, "%02d:%02d", hour, minute);
        printf("%s vs %s at %s in %s\n", matches[matchIndex].team1, matches[matchIndex].team2, matches[matchIndex].time, matches[matchIndex].venue);

        // Increment time by match length only after all matches at the same time are scheduled
        if ((match + 1) % numVenues == 0 || match + 1 == matchesPerRound) {
            minute += matchLength;
            if (minute >= 60) {
                minute -= 60;
                hour++;
            }
        }

        matchIndex++;
    }
}

// Function to display fixtures sorted by venue
void displayFixturesByVenue(Match *matches, int numMatches, Venue venues[], int numVenues) {
    printf("\nFixtures by Venue:\n");

    // Sort venues alphabetically
    for (int i = 0; i < numVenues; i++) {
        for (int j = i + 1; j < numVenues; j++) {
            if (strcmp(venues[i].name, venues[j].name) > 0) {
                Venue temp = venues[i];
                venues[i] = venues[j];
                venues[j] = temp;
            }
        }
    }

    for (int venueIndex = 0; venueIndex < numVenues; venueIndex++) {
        printf("\n--- %s ---\n", venues[venueIndex].name);
        for (int i = 0; i < numMatches; i++) {
            if (strcmp(matches[i].venue, venues[venueIndex].name) == 0) {
                printf("%s vs %s at %s\n", matches[i].team1, matches[i].team2, matches[i].time);
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int choice;
    Team teams[MAX_TEAMS];
    Venue venues[MAX_VENUES];
    Match matches[MAX_MATCHES_PER_DAY];
    int numTeams = 0, numVenues = 0;

    while (1) {
        printf("\nSports Fixture Management Menu:\n");
        printf("1. Add Venues\n");
        printf("2. Add Teams\n");
        printf("3. Generate Fixtures\n");
        printf("4. Display Fixtures by Venue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clear input buffer

        switch (choice) {
            case 1:
                if (numVenues == 0) {
                    printf("Enter the number of venues: ");
                    scanf("%d", &numVenues);
                    clearInputBuffer(); // Clear input buffer

                    if (numVenues > MAX_VENUES) {
                        printf("Maximum number of venues exceeded! Only %d venues allowed.\n", MAX_VENUES);
                        numVenues = MAX_VENUES;
                    }

                    getVenues(venues, numVenues);
                } else {
                    printf("Venues have already been added.\n");
                }
                break;
            case 2:
                if (numTeams == 0) {
                    printf("Enter the number of teams: ");
                    scanf("%d", &numTeams);
                    clearInputBuffer(); // Clear input buffer

                    if (numTeams > MAX_TEAMS) {
                        printf("Maximum number of teams exceeded! Only %d teams allowed.\n", MAX_TEAMS);
                        numTeams = MAX_TEAMS;
                    }

                    getTeams(teams, numTeams);
                } else {
                    printf("Teams have already been added.\n");
                }
                break;
            case 3:
                if (numTeams > 1 && numVenues > 0) {
                    int matchLength;
                    printf("Enter match length in minutes: ");
                    scanf("%d", &matchLength);
                    clearInputBuffer(); // Clear input buffer
                    generateFixtures(teams, numTeams, venues, numVenues, matches, matchLength);
                } else {
                    printf("At least two teams and one venue are required.\n");
                }
                break;
            case 4:
                displayFixturesByVenue(matches, numTeams / 2, venues, numVenues);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
