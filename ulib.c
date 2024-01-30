#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "mmu.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}


int th_create(void (*func)(void *, void *), void* arg1, void* arg2)
{
  void *stack = malloc(PGSIZE);
  if (stack == 0)
      return -1;
  if ((uint)stack % PGSIZE != 0)
      stack += PGSIZE - ((uint)stack % PGSIZE);

  return clone(stack, func, arg1, arg2 );
}

int th_join(int tid)
{
  int retval;
  void *stack;
  retval = join(tid, &stack);
  free(stack);
  return retval;
}

int lk_init(lock_t *lock)
{
  lock->flag = 0;
  return 0;
}

void lk_acquire(lock_t *lock){
  while(xchg(&lock->flag, 1) != 0);
}

void lk_release(lock_t *lock){
	xchg(&lock->flag, 0);
}