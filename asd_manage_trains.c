/**
 * Edoardo Conti
 * ALGORITHMS AND DATA STRUCTURES
 * summer session Project 2016/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asd_manage_trains_lib.h"

int main(int argc, char *argv[]) {
	FILE *datafile = NULL;
	char city_from[50],
		 city_to[50];
	int i = 0,
		j = 0,
		k = 0,
		z = 0,
		nStations = 0,
		SL = 0,
		found = 0,
		travel_km, travel_time;

	if(argc != 2) {
		/* stop running */
		printf("Utilizzo errato del programma. Sintassi d'esecuzione corretta:\n./asd_manage_trains <file database>\n");
	} else {
		/* open file */
		datafile = fopen(argv[1], "r");
		if(datafile) {
			/* get number of stations -> $nStations */
			fscanf(datafile, "%d\n", &nStations);

			/* graph = array of pointers V */
			vertex_graph_t *head[nStations];
			/* adjacency matrix TODO */
			char* matrix[nStations][nStations];
			/* join between city <==> index */
			char join[nStations][50];
			/* init join associations */
			for(z=0; z<=nStations; z++)
				strcpy(join[z], "-");
			/* init matrix */
			for(j=0; j<nStations; j++)
				for(i=0; i<nStations; i++)
					matrix[i][j] = "0";
			int ns[nStations];

			i = j = 0;
			while(i != nStations) {
				/* get number of Stations Linked to the i-th -> $SL */
				fscanf(datafile, "%d\n", &SL);

				ns[i] = SL;

				while(j != SL) {
					/* get data for each link betwheen cities */
					fscanf(datafile, "%s %s %d %d\n", city_from, city_to, &travel_km, &travel_time);

					/* first add in join array */
					if(i == 0 && j == 0)
						strcpy(join[k++], city_from);

					/* search $city_to in join array */
					for(z=0; z<nStations; z++)
						if(strcmp(join[z], city_to) == 0)
							found = 1;

					/* add $city_to in join array if not founded */
					if(found == 0)
						strcpy(join[k++], city_to);

					/* populate adjacency matrix after mapping the join table */
					populateMatrix(nStations, matrix, join, city_from, city_to, travel_km, travel_time);

					/* reset found flag */
					found = 0;
					j++;
				}
				/* reset counters */
				j = 0;

				i++;
			}

			/* process matrix */
			matrix2graph(nStations, matrix, join, ns, head);

			/* user join and dijkstra process */
			userJoin(nStations, head, join);
		}
		fclose(datafile);
	}
	return 0;
}
