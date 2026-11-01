#include "Task.h"
#include "Job.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TaskSet *create_taskset(char *task_file) {
    FILE *tf = fopen(task_file, "r");
    if (tf == NULL) {
        fprintf(stderr, "Error opening task file.");
        exit(1);
    }
    TaskSet *taskset = (TaskSet*) malloc(sizeof(TaskSet));
    if (taskset == NULL) {
        fprintf(stderr, "Error allocating memory for task set.");
        exit(1);
    }
    taskset->n_tasks = 0;
    taskset->tasks = (Task**) calloc(MAX_TASKS, sizeof(Task));
    char line[100];
    int id = 0;
    while (fgets(line, sizeof(line), tf)) {
        char offset[10] = "          ";
        char wcet[10] = "          ";
        char deadline[10] = "          ";
        char period[10] = "          ";
        char *vals[4] = {offset, wcet, deadline, period};
        int k = 0;
        for (int j = 0; j < 4; j++) {
            char buffer[10] = "          ";
            int i = 0;
            while (1) {
                char ch = line[k];
                if (ch == ';' || ch == '\n') {
                    buffer[i+1] = '\0';
                    strcpy(vals[j], buffer);
                    k++;
                    i = 0;
                    break;
                }
                buffer[i] = ch;
                i++;
                k++;
            }
        }
        Task *new_task = create_task(id, atoi(offset), atoi(wcet), atoi(deadline), atoi(period));
        taskset->tasks[id] = new_task;
        taskset->n_tasks++;
        id++;
    }
    fclose(tf);
    
    return taskset;
}

Task *create_task(int id, int offset, int wcet, int deadline, int period) {
    Task *task = (Task*) malloc(sizeof(Task));
    if (task == NULL) {
        fprintf(stderr, "Error allocating memory for new task");
        return NULL;
    }
    task->id = id;
    task->offset = offset;
    task->wcet = wcet;
    task->deadline = deadline;
    task->period = period;

    return task;
}

Job *release_job(Task *task, int arrival_time) {
    if (arrival_time % task->period == 0) {
        Job *new_job_p = malloc(sizeof(Job));
        if (new_job_p == NULL) {
            fprintf(stderr, "Error allocating memory for new job");
            return NULL;
        }
        new_job_p->duration = task->wcet;
        new_job_p->release_time = arrival_time;
        new_job_p->abs_deadline = arrival_time + task->deadline;
        new_job_p->exec_time = 0;
        new_job_p->period = task->period;

        return new_job_p;
    }
    return NULL;
}

void print_task(Task *task) {
    printf("Task n°%d\n", task->id);
    printf("  Offset : %d | ", task->offset);
    printf("  WCET : %d | ", task->wcet);
    printf("  Deadline : %d | ", task->deadline);
    printf("  Period : %d\n", task->period);
}
