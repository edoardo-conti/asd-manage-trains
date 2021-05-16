# asd-manage-trains
Programma ANSI C per la gestione dell’orario dei treni di una rete ferroviaria. 
L'implementazione prevede le seguenti elaborazioni:
1. Acquisisce un file di testo con i collegamenti tra le varie stazioni, la distanza tra le stesse (in Km) e i relativi tempi di percorrenza dei treni (in minuti).
2. Inserisce i dati in una opportuna struttura dati.
3. Calcola il percorso più breve tra due stazioni selezionate dall’utente, in base al tempo e in base alla distanza (Dijkstra).
4. Calcola una serie di statistiche sui pesi degli archi del grafo come valore massimo, media, mediana, ecc. e l'analisi complessità computazionale.
