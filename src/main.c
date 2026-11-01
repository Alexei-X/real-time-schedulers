#include "Schedulers.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    enum Scheduling scheduling;
    if (argc < 4) {
        printf("Usage : project <task_file> -a edf|rm|dm [-m <#cores>] [-h ff|bf|nf|wf] [-s du|iu]\n");
        exit(1);
    }
    printf("Input File : %s\n", argv[1]);
    TaskSet *taskset = create_taskset(argv[1]);
    printf("Algorithm used : ");
    if (!strcmp(argv[3], "edf")) {
        scheduling = EDF;
        printf("Earliest Deadline First\n");
    } else if (!strcmp(argv[3], "rm")) {
        scheduling = RM;
        printf("Rate Monotonic\n");
    } else if (!strcmp(argv[3], "dm")) {
        scheduling = DM;
        printf("Deadline Monotonic\n");
    }

    for (int i = 0; i < taskset->n_tasks; i++) {
        print_task(taskset->tasks[i]);
    }

    schedule_tasks(scheduling, taskset);

    return 0;
}
