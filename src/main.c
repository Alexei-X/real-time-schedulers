#include "Schedulers.h"
#include <stdio.h>
#include <string.h>

TaskSet* parse_arguments(int argc, char** argv, enum Scheduling* scheduling_p, enum Heuristic* heuristic_p, enum Sorting* sorting_p, int* n_cores_p);

int main(int argc, char** argv) {
    enum Scheduling scheduling;
    enum Heuristic heuristic = FF;
    enum Sorting sorting = DU;
    int n_cores = 1;
    
    TaskSet* taskset = parse_arguments(argc, argv, &scheduling, &heuristic, &sorting, &n_cores);

    for (int i = 0; i < taskset->n_tasks; i++) {
        print_task(taskset->tasks[i]);
    }

    schedule_tasks(scheduling, taskset);

    return 0;
}

TaskSet* parse_arguments(int argc, char** argv, enum Scheduling* scheduling_p, enum Heuristic* heuristic_p, enum Sorting* sorting_p, int* n_cores_p) {
    if (argc < 4) {
            printf("Usage : project <task_file> -a edf|rm|dm [-m <#cores>] [-h ff|bf|nf|wf] [-s du|iu]\n");
            exit(1);
    }
    printf("Input File : %s\n", argv[1]);
    TaskSet *taskset = create_taskset(argv[1]);
    printf("Algorithm used : ");
    if (!strcmp(argv[3], "edf")) {
        *scheduling_p = EDF;
        printf("Earliest Deadline First\n");
    } else if (!strcmp(argv[3], "rm")) {
        *scheduling_p = RM;
        printf("Rate Monotonic\n");
    } else if (!strcmp(argv[3], "dm")) {
        *scheduling_p = DM;
        printf("Deadline Monotonic\n");
    }
    if (argc > 4) {
        for (int i = 4; i < argc; i+=2) {
            if (!strcmp(argv[i], "-m")) {
                *n_cores_p = atoi(argv[i+1]);
                printf("Number of cores : %d\n", *n_cores_p);
            } else if (!strcmp(argv[i], "-h")) {
                if (!strcmp(argv[i+1], "bf")) {
                    printf("Heuristic : Best Fit\n");
                    *heuristic_p = BF;
                } else if (!strcmp(argv[i+1], "nf")) {
                    printf("Heuristic : Next Fit\n");
                    *heuristic_p = NF;
                } else if (!strcmp(argv[i+1], "wf")) {
                    printf("Heuristic : Worst Fit\n");
                    *heuristic_p = WF;
                } else if (!strcmp(argv[i+1], "ff")) {
                    printf("Heuristic : First Fit\n");
                }
            } else if (!strcmp(argv[i], "-s")) {
                if (!strcmp(argv[i+1], "iu")) {
                    printf("Sorting : Increasing Utilization\n");
                    *sorting_p = IU;
                } else if (!strcmp(argv[i+1], "du")) {
                    printf("Sorting : Decreasing Utilization\n");
                }
            }
        }
    }
    return taskset;
}
