#include <test_processes.h>

int64_t test_processes(uint64_t argc, char *argv[])
{
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t max_processes;

  if (argc != 1)
    return -1;

  if ((max_processes = satoi(argv[0])) <= 0)
    return -1;

  p_rq p_rqs[max_processes];

  while (1)
  {

    // Create max_processes processes
    for (rq = 0; rq < max_processes; rq++)
    {
      char *argv[] = {"Idle Process"};
      p_rqs[rq].pid = newProcess(&idleProcess, 1, argv, BACKGROUND, NULL);

      if (p_rqs[rq].pid == -1)
      {
        printf("test_processes: ERROR creating process\n");
        return -1;
      }
      else
      {
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0)
    {

      for (rq = 0; rq < max_processes; rq++)
      {
        action = GetUniform(100) % 2;

        switch (action)
        {
        case 0:
          if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == WAITING)
          {
            if (killProcess(p_rqs[rq].pid) == -1)
            {
              printf("test_processes: ERROR killing process\n");
              return -1;
            }
            p_rqs[rq].state = KILLED;
            alive--;
          }
          break;

        case 1:
          if (p_rqs[rq].state == RUNNING)
          {
            if (blockProcess(p_rqs[rq].pid) == -1)
            {
              printf("test_processes: ERROR blocking process\n");
              return -1;
            }
            p_rqs[rq].state = WAITING;
          }
          break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < max_processes; rq++)
        if (p_rqs[rq].state == WAITING && GetUniform(100) % 2)
        {
          if (unblockProcess(p_rqs[rq].pid) == -1)
          {
            printf("test_processes: ERROR unblocking process\n");
            return -1;
          }
          p_rqs[rq].state = RUNNING;
        }
    }
  }
}
