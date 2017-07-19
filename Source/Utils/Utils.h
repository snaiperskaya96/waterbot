//
// Created by Jury Verrigni on 19/07/2017.
//

#ifndef WATERBOT_UTILS_H
#define WATERBOT_UTILS_H

#include <cstring>
#include <sched.h>

class Utils
{
public:
    static void SetMaxPriority(void) {
        struct sched_param sched;
        memset(&sched, 0, sizeof(sched));
        sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
#ifdef __unix__
        sched_setscheduler(0, SCHED_FIFO, &sched);
#endif
    }

    static void SetDefaultPriority(void) {
        struct sched_param sched;
        memset(&sched, 0, sizeof(sched));
        sched.sched_priority = 0;
#ifdef __unix__
        sched_setscheduler(0, SCHED_OTHER, &sched);
#endif
    }

};

#endif //WATERBOT_UTILS_H
