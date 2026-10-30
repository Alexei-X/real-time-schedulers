#include "Job.h"
#include <stdio.h>

bool is_deadline_missed(Job *job, int time) {
    return (time > job->abs_deadline);
}

bool schedule(Job *job, int time) {
    job->exec_time += time;
    return (job->exec_time >= job->duration);
}

void print_job(Job *job) {
    printf("Job : \n");
    printf("\t duration : %d\n", job->duration);
    printf("\t release time : %d\n", job->release_time);
    printf("\t absolute deadline : %d\n", job->abs_deadline);
    printf("\t execution time : %d\n", job->exec_time);
    printf("\t period : %d\n", job->period);
}

