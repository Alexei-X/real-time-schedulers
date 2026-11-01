#include "Schedulers.h"
#include "Job.h"
#include <stdio.h>

Job *rate_monotonic(Job **jobs, int n_jobs, int *job_index) {
    int k = 0;
    while ((jobs[k] == NULL) && (k < n_jobs)) {
        k++;
    }
    Job *current_min = jobs[k];
    int min_index = k;
    for (int i = k+1; i < n_jobs; i++) {
        if (jobs[i] == NULL) continue;
        if (jobs[i]->period < current_min->period) {
            current_min = jobs[i];
            min_index = i;
        }
    }
    *job_index = min_index;
    return current_min;
}

Job *deadline_monotonic(Job **jobs, int n_jobs) {
    return NULL;
}

Job *earliest_deadline_first(Job **jobs, int n_jobs) {
    int k = 0;
    while (jobs[k] == NULL && k < n_jobs) {
        k++;
    }
    Job *current_min = jobs[k];
    for (int i = k+1; i < n_jobs; i++) {
        if (jobs[i] == NULL) {
            continue;
        }
        if (jobs[i]->abs_deadline < current_min->abs_deadline) {
            current_min = jobs[i];
        }
    }
    return current_min;
}

bool check_for_missed_jobs(Job **jobs, int n_jobs, int time) {
    for (int i = 0; i < n_jobs; i++) {
        if (jobs[i] == NULL)  {
            continue;
        }
        if (is_deadline_missed(jobs[i], time)) {
            printf("Job missed is ");
            print_job(jobs[i]);
            return true;
        }
    }
    return false;
}

void print_current_jobs(Job **jobs, int n_jobs, int time) {
    printf("-------------------------------\n");
    printf("Currently %d jobs at time %d : \n", n_jobs, time);
    int seen_jobs = 0;
    for (int i = 0; seen_jobs < n_jobs; i++) {
        if (jobs[i] == NULL) continue;
        print_job(jobs[i]);
        seen_jobs++;
    }
    printf("-------------------------------\n");
}

int compute_t_max(TaskSet *taskset) {
    int current_max = taskset->tasks[0]->deadline;
    for (int i = 1; i < taskset->n_tasks; i++) {
        if (taskset->tasks[i]->deadline > current_max) {
            current_max = taskset->tasks[i]->deadline;
        }
    }
    printf("Time of simulation : %d\n", current_max);
    return current_max;
}

void schedule_tasks(enum Scheduling sch, TaskSet *taskset) {
    int t_max = compute_t_max(taskset);
    int final_schedule[taskset->n_tasks];
    int n_jobs = 0;
    Job **current_jobs = (Job**) malloc(MAX_N_JOBS * sizeof(Job*));
    Job *executing_job = NULL;
    int exec_job_idx;
    if (current_jobs == NULL) {
        fprintf(stderr, "Error allocating memory for jobs.");
        exit(1);
    }
    for (int ts = 0; ts < t_max; ts++) {
        printf("\n*********** ITERATION : %d **************\n", ts);
        if(check_for_missed_jobs(current_jobs, n_jobs, ts)) {
            printf("One job missed its deadline. Task set not schedulable.");
            exit(0);
        }
        if (executing_job != NULL) {
            printf("Executing Job : ");
            print_job(executing_job);
            if(schedule(executing_job, 1)) {
                printf("Current job finished at ts : %d\n", ts);
                Job *job_to_free = current_jobs[exec_job_idx];
                free(job_to_free);
                current_jobs[exec_job_idx] = NULL;
                executing_job = NULL;
                n_jobs--;
            }
        }
        for (int task_idx = 0; task_idx < taskset->n_tasks; task_idx++) {
            Job *potential_job = release_job(taskset->tasks[task_idx], ts);
            if (potential_job != NULL) {
                current_jobs[n_jobs++] = potential_job;
            }
        }
        print_current_jobs(current_jobs, n_jobs, ts);
        switch (sch) {
            case RM:
                //printf("Rate Monotonic Scheduling\n");
                executing_job = rate_monotonic(current_jobs, n_jobs, &exec_job_idx);
                break;
            case DM:
                //printf("Deadline Monotonic Scheduling\n");
                executing_job = deadline_monotonic(current_jobs, n_jobs);
                break;
            case EDF:
                //printf("Earliest Deadline First Scheduling\n");
                executing_job = earliest_deadline_first(current_jobs, n_jobs);
                break;
        }
    }
}
