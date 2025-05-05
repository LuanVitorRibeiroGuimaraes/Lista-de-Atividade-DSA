#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_POINTS 100

typedef struct {
    double x, y;
} Point;

// Função de comparação para ordenar os pontos com base na distância até a origem
int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    
    // Distância euclidiana direta da origem (0, 0) para os pontos
    double d1 = sqrt(p1->x * p1->x + p1->y * p1->y); 
    double d2 = sqrt(p2->x * p2->x + p2->y * p2->y);
    
    return (d1 > d2) - (d1 < d2);  // Retorna -1, 0 ou 1 dependendo da comparação
}

int main() {
    FILE *in = fopen("L0Q1.in", "r");
    FILE *out = fopen("L0Q1.out", "w");  // Alterado para .txt

    if (!in || !out) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char line[1024];
    Point points[MAX_POINTS];
    int n;

    // Processa cada linha do arquivo de entrada
    while (fgets(line, sizeof(line), in)) {
        if (strncmp(line, "points", 6) != 0) continue;  // Procura por "points"

        n = 0;
        char *ptr = strchr(line, '(');
        while (ptr && n < MAX_POINTS) {
            double x, y;
            sscanf(ptr, "(%lf,%lf)", &x, &y);
            points[n++] = (Point){x, y};
            ptr = strchr(ptr + 1, '(');  // Encontra o próximo ponto
        }

        if (n == 0) continue;  // Se não houver pontos, pula a linha

        // Ordenar os pontos com base na distância até a origem
        qsort(points, n, sizeof(Point), compare);

        // Calcular a distância total e a distância do atalho
        double total_distance = 0.0;
        for (int i = 1; i < n; i++) {
            total_distance += sqrt((points[i].x - points[i - 1].x) * (points[i].x - points[i - 1].x) + 
                                   (points[i].y - points[i - 1].y) * (points[i].y - points[i - 1].y));
        }

        // Distância do atalho entre o primeiro e o último ponto
        double shortcut = sqrt((points[n - 1].x - points[0].x) * (points[n - 1].x - points[0].x) +
                               (points[n - 1].y - points[0].y) * (points[n - 1].y - points[0].y));

        // Escrever o resultado no arquivo de saída
        fprintf(out, "points");
        for (int i = 0; i < n; i++) {
            fprintf(out, " (%.0f,%.0f)", points[i].x, points[i].y);
        }

        fprintf(out, " distance %.2f shortcut %.2f\n", total_distance, shortcut);
    }

    fclose(in);
    fclose(out);
    printf("Arquivo L0Q1.out gerado com sucesso!\n");
    return 0;
}
