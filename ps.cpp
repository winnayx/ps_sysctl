#include <iostream>
#include <string.h>
#include <sys/sysctl.h>

using namespace std;

int main() {
  struct kinfo_proc *res = NULL;
  size_t res_size = 0;
  
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  int mib_len = 4; 

  if (sysctl(mib, mib_len, NULL, &res_size, NULL, 0) == -1) {
    perror("sysctl");
  }
  
  if (!(res = (struct kinfo_proc *)malloc(res_size))) {
    perror("malloc");
  } 

  if (sysctl (mib, mib_len, res, &res_size, NULL, 0) == -1) {
    free(res);
    perror("sysctl");
  }
   
  int res_count = res_size / sizeof(struct kinfo_proc);
  int tty_offset = 0;

  for (int i = res_count - 1; i >= 0; i--) {
    struct extern_proc curr = res[i].kp_proc;
    if (res[i].kp_eproc.e_tdev > 0 && strncmp(curr.p_comm, "login", 5)) {
      if (!tty_offset) tty_offset = res[i].kp_eproc.e_tdev;  
      cout << "PID: " << curr.p_pid 
	<< "  TTY: ttys00"<< res[i].kp_eproc.e_tdev - tty_offset
	<< "  CMD: " << curr.p_comm << endl;
    } 
  }

  free(res);
  return 0;
}

