#define MAX_BUFFER_SIZE 81
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Structures*/
typedef struct Team
{
	char* teamname;
	int matchesPlayed;
	int score;
}Team;

typedef struct matchDay
{
	int day;
	int month;
	int year;
	Team *team1;
	Team *team2;
	Team *isWinner;
	bool isPlayed;

}matchDay;

typedef struct Season
{
	Team *ranking;
	matchDay *calendar;
	int totalMatches;
	int matchesPlayed;
	int remainingMatches;

}Season;

/*Function prototypes*/
void initSeason(Season *obj);//Constructor for season
void bufferCheck(char string[]);//If there is a newline at the end of the string, it deletes it.
void initTeams(Team **ranking, int n);//Initialises the ranking of teams
void initCalendar(matchDay **calendar, Season *ranking, int n, int teams);//Initiases the calender of matchdays
void printCalendar(const Season **season);
void updateSeason(Season **season, int winner, int index);
void printRanking(Season **season);


int main(void)
{
	char buffer[MAX_BUFFER_SIZE];
	int index = 0, winner;

	Season *footbalSeason = (Season*)malloc(sizeof(Season));

	if (footbalSeason == NULL)
	{
		printf("Memory allocation for Season failed...");
		return -1;
	}

	initSeason(footbalSeason);

	while (footbalSeason->matchesPlayed != footbalSeason->totalMatches)
	{
		printCalendar(&footbalSeason);
	
		printf("Next match:\n");

		printf("Match: %d on %d/%d/%d\n", index + 1, footbalSeason->calendar[index].day, footbalSeason->calendar[index].month, footbalSeason->calendar[index].year);
		printf("%s vs %s\n", footbalSeason->calendar[index].team1->teamname, footbalSeason->calendar[index].team2->teamname);
		printf("Winner (1/2): \n");
		fgets(buffer, MAX_BUFFER_SIZE, stdin);
		bufferCheck(buffer);
		winner = atoi(buffer);

		updateSeason(&footbalSeason, winner, index);

		printRanking(&footbalSeason);
	}
	
	//determineTop3OfTheSeaon(&footbalSeason);

	return 0;
}

void printRanking(Season **season)
{
	qsort(*season, (*season)->)
}

void updateSeason(Season **season, int winner , int index)
{
	(*season)->matchesPlayed += 1;
	(*season)->remainingMatches = ((*season)->totalMatches) - (*season)->matchesPlayed;

	(*season)->calendar[index].isPlayed = true;
	(*season)->calendar[index].team1->matchesPlayed += 1;
	(*season)->calendar[index].team2->matchesPlayed += 1;

	if(winner == 1)
	{
		(*season)->calendar[index].isWinner = (*season)->calendar[index].team1;
		(*season)->calendar[index].team1->score += 1;
	}
	
	else if(winner == 2)
	{
		(*season)->calendar[index].isWinner = (*season)->calendar[index].team2;
		(*season)->calendar[index].team2->score += 1;
	}
}

void printCalendar(const Season **season)
{
	int n = (*season)->totalMatches;
	printf("\nCalendar: \n");

	for (int i = 0; i < n; ++i)
	{
		char* team1 = (*season)->calendar[i].team1->teamname;
		char* team2 = (*season)->calendar[i].team2->teamname;

		printf("\nMatchday %d:\n", i + 1);
		printf("Date: %d/%d/%d\n", (*season)->calendar[i].day, (*season)->calendar[i].month, (*season)->calendar[i].year);
		printf("matchup: ");
		printf("%s", team1);
		printf(" vs ");
		printf("%s\n", team2);


		if ((*season)->calendar[i].isPlayed == false)
		{
			printf("Match has not been played.\n");
			printf("___________________________________");
		}

		else
		{
			printf("Winner: %s\n", (*season)->calendar[i].isWinner->teamname);
			printf("___________________________________");
		}
	}
}

void initSeason(Season *season)
{
	char buffer[MAX_BUFFER_SIZE];
	int totalTeams;
	int totalMatches;

	printf("How many teams would you like to register?: ");
	fgets(buffer, MAX_BUFFER_SIZE, stdin);
	bufferCheck(buffer);
	totalTeams = atoi(buffer);

	totalMatches = ((totalTeams - 1) * totalTeams) / 2;

	season->totalMatches = totalMatches;
	season->remainingMatches = totalMatches;
	season->matchesPlayed = 0;


	initTeams(&(season->ranking), totalTeams);
	initCalendar(&(season->calendar), season, totalMatches, totalTeams);
}

/*Initialises the calendar*/
void initCalendar(matchDay **calendar, Season *season, int n, int teams)
{
	int calendarIndex = 0;
	int day = 1;
	int month = 1;
	int year = 2016;

	*calendar = (matchDay*)malloc(sizeof(matchDay) * (n));

	if (*calendar == NULL)
	{
		printf("Memory allocation calendar failed...\n");
		EXIT_FAILURE;
	}

	for (int i = 0; i < teams; ++i)
	{
		if (i == (teams - 1))
			break;

		for (int j=i+1; j <teams; ++j)
		{

			(*calendar)[calendarIndex].day = day;
			(*calendar)[calendarIndex].month = month;
			(*calendar)[calendarIndex].year = year;
			(*calendar)[calendarIndex].isPlayed = false;
			(*calendar)[calendarIndex].isWinner = NULL;
			(*calendar)[calendarIndex].team1 = &season->ranking[i];
			(*calendar)[calendarIndex].team2 = &season->ranking[j];

			++calendarIndex;
			++day;
		}
	}
}


/*Initialises the team*/
void initTeams(Team **ranking, int n)
{
	char buffer[MAX_BUFFER_SIZE];

	*ranking = (Team*)malloc(sizeof(Team) * n);

	//checks wether memory reservation was succesfull
	if (*ranking == NULL)
	{
		printf("Memery allocation for ranking failed\n");
		EXIT_FAILURE;
	}
	
	//Initliases teams
	for (int i = 0; i < n; ++i)
	{
		(*ranking)[i].matchesPlayed = 0;
		(*ranking)[i].score = 0;

		printf("\nTeam %d: please enter your teamname\n", i+1);
		fgets(buffer, MAX_BUFFER_SIZE, stdin);
		bufferCheck(buffer);

		(*ranking)[i].teamname = (char*)malloc(strlen(buffer) + 1);

		if ((*ranking)[i].teamname == NULL)
		{
			printf("Memory allocation teamname of team %d failed\n", i);
			EXIT_FAILURE;
		}

		strcpy((*ranking)[i].teamname, buffer);
	}
}

/*Deteles the newline at the end of the string, if there is one.*/
void bufferCheck(char string[])
{
	if (string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = '\0';
}
