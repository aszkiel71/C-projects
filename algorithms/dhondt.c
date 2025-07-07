#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTY_NAME_LENGTH 50
#define MAX_SEATS 50

typedef struct {
  char name[MAX_PARTY_NAME_LENGTH];
  int votes;
  int seats;
  double divisor;
} Party;

typedef struct {
  int partyIndex;
  double quotient;
} Quotient;

int main() {
  int numParties;
  int totalSeats;

  printf("Enter the number of parties: ");
  if (scanf("%d", &numParties) != 1 || numParties <= 0) {
    fprintf(stderr, "Invalid number of parties.\n");
    return EXIT_FAILURE;
  }

  Party* parties = (Party*)malloc(sizeof(Party) * numParties);
  if (parties == NULL) {
    fprintf(stderr, "Memory allocation failed for parties.\n");
    return EXIT_FAILURE;
  }

  while (getchar() != '\n');

  for (int i = 0; i < numParties; i++) {
    printf("Enter name for Party %d: ", i + 1);
    if (fgets(parties[i].name, MAX_PARTY_NAME_LENGTH, stdin) == NULL) {
      fprintf(stderr, "Error reading party name.\n");
      free(parties);
      return EXIT_FAILURE;
    }
    parties[i].name[strcspn(parties[i].name, "\n")] = '\0';
    parties[i].seats = 0;
  }

  for (int i = 0; i < numParties; i++) {
    printf("Enter votes for %s: ", parties[i].name);
    if (scanf("%d", &parties[i].votes) != 1 || parties[i].votes < 0) {
      fprintf(stderr, "Invalid vote count for %s.\n", parties[i].name);
      free(parties);
      return EXIT_FAILURE;
    }
  }

  printf("Enter the total number of seats to distribute: ");
  if (scanf("%d", &totalSeats) != 1 || totalSeats <= 0) {
    fprintf(stderr, "Invalid total number of seats.\n");
    free(parties);
    return EXIT_FAILURE;
  }

  for (int seat = 0; seat < totalSeats; seat++) {
    int bestPartyIndex = -1;
    double maxQuotient = -1.0;

    for (int i = 0; i < numParties; i++) {
      parties[i].divisor = (double)parties[i].votes / (parties[i].seats + 1);

      if (parties[i].divisor > maxQuotient) {
        maxQuotient = parties[i].divisor;
        bestPartyIndex = i;
      }
    }

    if (bestPartyIndex != -1) {
      parties[bestPartyIndex].seats++;
    }
  }

  printf("\n--- D'Hondt Method Results ---\n");
  for (int i = 0; i < numParties; i++) {
    printf("Party: %-20s Votes: %-10d Seats: %d\n", parties[i].name,
           parties[i].votes, parties[i].seats);
  }

  free(parties);

  return EXIT_SUCCESS;
}
