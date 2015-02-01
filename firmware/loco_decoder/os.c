#include "os.h"

volatile static os_task_entry_t *task_head;
volatile static os_time_t os_timer;

void os_init()
{
	task_head = NULL;
}

void os_time_get (os_time_t *time)
{
	
}

void os_task_remove (os_task_entry_t *ent)
{
	os_task_entry_t *cur, *prev = NULL;

	for (cur = task_head; cur != NULL; cur = cur->next)
	{
		if (cur == ent)
		{
			if (prev == NULL)
			{
				task_head = cur->next;
			} else
			{
				prev->next = cur->next;
			}
			return;
		}
		prev = cur;
	}
}

void os_idle_tick ()
{
	os_task_entry_t *cur;

	for (cur = task_head; cur != NULL; cur = cur->next)
	{
		os_return_t rv = cur->task (cur);
		if (rv == OS_CALLBACK_AGAIN)
			continue;

		if (rv == OS_CALLBACK_REMOVE)
			os_task_remove (cur);
	}
}

void os_add_task (os_task_t *task)
{
	task->next = task_head;
	task_head = task;
}
