#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>

using namespace std;

int main() {
  printf("Hello world");
  struct kinfo_proc *proc = NULL;
  size_t size = 0; 
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  int mib_len = 4; 
  int ret = sysctl (mib, mib_len, NULL, &size, NULL, 0);
  if (ret == -1) {
    // errno is set to indicate the error too
    cout << "errno: " << errno << endl;
    perror("sysctl");
  } 

  int proc_len = 
  for (int i = 0; i < 10; i++) {
    cout << "ret " << ret << endl;
    cout << "mib " << *mib << endl; 
    ret = sysctl (mib, mib_len, NULL, NULL, NULL, 0);
  }
  

  return 0;
}
