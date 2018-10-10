/*
	@brief:Floyd×î¶ÌÂ·¾¶
	@author:WavenZ
	@time:2018/10/10
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdlib.h>
#include "MGraph.h"

typedef struct {
	int Length[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}ShortPath;

void ShortestPath_FLOYD(MGraph *G, ShortPath *D) {

	for (int v = 0; v < G->vexnum; ++v)
		for (int w = 0; w < G->vexnum; ++w) {
			D->Length[v][w] = G->arcs[v][w].adj;
			for (int u = 0; u < G->vexnum; ++u) D->PathMatrix[v][w][u] = 0;
			if (D->Length[v][w] < INFINITY) {
				D->PathMatrix[v][w][v] = 1;
				D->PathMatrix[v][w][w] = 1;
			}
		}
	for(int u=0;u<G->vexnum;++u)
		for(int v=0;v<G->vexnum;++v)
			for (int w = 0; w < G->vexnum; ++w) {
				if (D->Length[v][u] + D->Length[u][w] < D->Length[v][w]) {
					D->Length[v][w] = D->Length[v][u] + D->Length[u][w];
					for (int i = 0; i < G->vexnum; ++i) {
						D->PathMatrix[v][w][i] = D->PathMatrix[v][u][i] || D->PathMatrix[u][w][i];
					}

				}
			}
}

void printLength(MGraph *G, ShortPath *D) {
	printf("\n");
	for (int i = 0; i < G->vexnum; ++i) {
		for (int j = 0; j < G->vexnum; ++j) {
			if (D->Length[i][j] == INFINITY)
				printf("¡Þ\t");
			else
				printf("%d\t", D->Length[i][j]);
		}
		printf("\n");
	}
}



int main(int argc, char *argv[]) {
	MGraph G;
	ShortPath D;
	CreateMGraph(&G);
	printMGraph(G);
	ShortestPath_FLOYD(&G, &D);
	printLength(&G, &D);
	system("pause");
	return 1;
}