#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/sysctl.h>

using namespace std;

int main(int argc, char** argv) {
  struct kinfo_proc *res = NULL;
  size_t res_size = 0;
  
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  int mib_len = 4; 

  /* first sysctl retrieves res_size for malloc */
  if (sysctl(mib, mib_len, NULL, &res_size, NULL, 0) == -1) {
    perror("sysctl");
  }
  
  if (!(res = (struct kinfo_proc *)malloc(res_size))) {
    perror("malloc");
  } 

  /* second sysctl populates res with kern proc info */
  if (sysctl (mib, mib_len, res, &res_size, NULL, 0) == -1) {
    free(res);
    perror("sysctl");
  }
   
  int res_count = res_size / sizeof(struct kinfo_proc);
  int tty_offset = 0;

  for (int i = res_count - 1; i >= 0; i--) {
    struct extern_proc curr = res[i].kp_proc;
    if (res[i].kp_eproc.e_tdev > 0 && 
	strncmp(curr.p_comm, "login", 5) && // excessive process
	!strstr(argv[0], curr.p_comm)) // skip curr process
    { 
      if (!tty_offset) tty_offset = res[i].kp_eproc.e_tdev; // offset used to retrieve tty 
      cout << " PID: " << curr.p_pid 
	<< "  TTY: ttys00"<< res[i].kp_eproc.e_tdev - tty_offset
	<< "  CMD: " << curr.p_comm << endl;
    } 
  }

  free(res);
  return 0;
}

