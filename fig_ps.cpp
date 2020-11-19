#include <iostream>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysctl.h>

using namespace std;

int main() {
  struct kinfo_proc *res = NULL;
  size_t res_size = 0;
 
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  int mib_len = 4; 

  int err = sysctl (mib, mib_len, res, &res_size, NULL, 0);
  if (err == -1) {
    // errno is set to indicate the error too
    cout << "errno: " << err << endl;
    perror("sysctl");
  }
  cout << "after first sysctl, res_size: " << res_size << endl; 
  
  res = (struct kinfo_proc *)malloc(res_size);
  err = sysctl (mib, mib_len, res, &res_size, NULL, 0);
   
  cout << "after second sysctl, res_size: " << res_size << endl; 
  int num_res = res_size / sizeof(struct kinfo_proc);

  for (int i = 0; i < num_res; i++) {
    cout << "pid: " << res[i].kp_proc.p_pid << " cmd" << res[i].kp_proc.p_comm<<  endl;
  } 

  return 0;
}

