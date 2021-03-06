#ifndef _HOUSEKEEPER_H
#define _HOUSEKEEPER_H
/*
 * Copyright (c) 2016 MariaDB Corporation Ab
 *
 * Use of this software is governed by the Business Source License included
 * in the LICENSE.TXT file and at www.mariadb.com/bsl.
 *
 * Change Date: 2019-01-01
 *
 * On the date above, in accordance with the Business Source License, use
 * of this software will be governed by version 2 or later of the General
 * Public License.
 */
#include <time.h>
#include <dcb.h>
#include <hk_heartbeat.h>
/**
 * @file housekeeper.h A mechanism to have task run periodically
 *
 * @verbatim
 * Revision History
 *
 * Date         Who             Description
 * 29/08/14     Mark Riddoch    Initial implementation
 *
 * @endverbatim
 */

typedef enum
{
    HK_REPEATED = 1,
    HK_ONESHOT
} HKTASK_TYPE;

/**
 * The housekeeper task list
 */
typedef struct hktask
{
    char *name;               /*< A simple task name */
    void (*task)(void *data); /*< The task to call */
    void *data;               /*< Data to pass the task */
    int frequency;            /*< How often to call the tasks (seconds) */
    time_t nextdue;           /*< When the task should be next run */
    HKTASK_TYPE type;         /*< The task type */
    struct hktask *next;      /*< Next task in the list */
} HKTASK;

extern void hkinit();
extern int  hktask_add(const char *name, void (*task)(void *), void *data, int frequency);
extern int  hktask_oneshot(const char *name, void (*task)(void *), void *data, int when);
extern int  hktask_remove(const char *name);
extern void hkshutdown();
extern void hkshow_tasks(DCB *pdcb);

#endif
