#include <stdlib.h>
#include <stdint.h>

typedef enum
{
	OS_CALLBACK_AGAIN =  0, /* keep in queue */
	OS_CALLBACK_REMOVE = 1, /* remove after return */
} os_return_t;

typedef struct
{
	uint16_t ms;
	uint16_t us;
} os_time_t;

struct os_task_entry_s;
typedef os_return_t (os_task_t*) (void * self);

typedef struct os_task_entry_s
{
	os_task_t *task;
	struct os_task_entry_s *next;
} os_task_entry_t;


void os_init(void);
void os_idle_tick (void);
void os_task_remove (os_task_entry_t *ent);
void os_add_task (os_task_t *task);
