#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#define MAX 30


typedef struct {
    char name[50];
    int age;
    float usage_time;
} Respondent;


double calculate_mean(Respondent respondents[], int n) {
    double total_time = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        total_time += respondents[i].usage_time;
    }
    return total_time / n;
}


double calculate_median(Respondent respondents[], int n) {
    float sorted[MAX];
    int i, j;
    for (i = 0; i < n; i++) {
        sorted[i] = respondents[i].usage_time;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                float temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    if (n % 2 == 0) {
        return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    } else {
        return sorted[n / 2];
    }
}


float calculate_mode(Respondent respondents[], int n) {
    int count[MAX] = {0};
    float values[MAX];
    int unique_count = 0;
    int i, j;


    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (respondents[i].usage_time == values[j]) {
                count[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            values[unique_count] = respondents[i].usage_time;
            count[unique_count] = 1;
            unique_count++;
        }
    }


    int max_count = 0;
    float mode = values[0];
    for (i = 0; i < unique_count; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            mode = values[i];
        }
    }


    return mode;
}


double calculate_variance(Respondent respondents[], int n, double mean) {
    double variance = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        variance += pow(respondents[i].usage_time - mean, 2);
    }
    return variance / n;
}


double calculate_std_dev(double variance) {
    return sqrt(variance);
}


double calculate_correlation(Respondent respondents[], int n) {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0;
    double sum_x2 = 0.0, sum_y2 = 0.0;
    int i;


    for (i = 0; i < n; i++) {
        sum_x += respondents[i].age;
        sum_y += respondents[i].usage_time;
        sum_xy += respondents[i].age * respondents[i].usage_time;
        sum_x2 += pow(respondents[i].age, 2);
        sum_y2 += pow(respondents[i].usage_time, 2);
    }


    double numerator = (n * sum_xy) - (sum_x * sum_y);
    double denominator = sqrt(((n * sum_x2) - pow(sum_x, 2)) * ((n * sum_y2) - pow(sum_y, 2)));


    return denominator != 0 ? numerator / denominator : 0;
}


void display_table(Respondent respondents[], int n) {
    int i;
    printf("%-20s%-10s%-15s\n", "Name", "Age", "Usage Time (hrs)");
    printf("%-20s%-10s%-15s\n", "-------------------", "--------", "----------------");
    for (i = 0; i < n; i++) {
        printf("%-20s%-10d%-15.2f\n", respondents[i].name, respondents[i].age, respondents[i].usage_time);
    }
}


int main() {
    Respondent respondents[MAX] = {
        {"Dina", 13, 4.0}, {"Raka", 14, 3.5}, {"Nina", 15, 5.0},
        {"David", 16, 4.5}, {"Eve", 17, 3.0}, {"Toni", 13, 4.2},
        {"Ica", 14, 3.8}, {"Hannah", 15, 2.5}, {"Melin", 16, 5.0},
        {"Rio", 17, 3.5}, {"Kara", 18, 4.7}, {"Lilik", 19, 3.0},
        {"Dita", 14, 4.0}, {"Nina", 15, 5.0}, {"Dafa", 16, 3.9},
        {"Fira", 18, 3.0}, {"Quinn", 13, 4.5}, {"Rachel", 14, 3.8},
        {"Yuni", 15, 4.0}, {"Tina", 17, 3.7}, {"Uma", 16, 4.2},
        {"Fira", 18, 4.0}, {"Wendy", 19, 3.0}, {"Tito", 16, 3.5},
        {"Gio", 17, 2.9}, {"Zidan", 15, 4.5}, {"Ali", 14, 4.0},
        {"Brian", 13, 3.8}, {"Clara", 15, 4.2}, {"Dylan", 14, 5.0}
    };


    int n = 30;


    printf("\n--- Tabel Data ---\n");
    display_table(respondents, n);


    double mean = calculate_mean(respondents, n);
    double median = calculate_median(respondents, n);
    float mode = calculate_mode(respondents, n);
    double variance = calculate_variance(respondents, n, mean);
    double std_dev = calculate_std_dev(variance);
    double correlation = calculate_correlation(respondents, n);


    printf("\nKesimpulan Statistik:\n");
    printf("Rata-rata: %.2f jam\n", mean);
    printf("Nilai tengah: %.2f jam\n", median);
    printf("Nilai yang sering muncul: %.2f jam\n", mode);
    printf("Variansi: %.2f\n", variance);
    printf("Standar Deviasi: %.2f\n", std_dev);
    printf("Korelasi antara usia dan waktu: %.2f\n", correlation);


    return 0;
}
