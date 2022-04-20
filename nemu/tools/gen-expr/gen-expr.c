#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[5000] = {};
int rind = 0;
static char code_buf[65536000 + 128] = {}; // a little larger than `buf`
static char* code_format =
"#include<stdio.h>\n"
"#include<exception>\n"
"int main(){"
"unsigned result;"
"try{"
"result = %s;"
"}catch("
"std::excep""tion"
"& e)"
"{"
"return 0;"
"}"
"printf(\"%%u\", result);"
"  return 0; "
"}";

char* opt[] = {
  "+","-","*","/"
};
static void gen(char * c) {
  strcpy(buf + rind, c);
  rind += strlen(c);
}
static int countN = 0;
static void gen_rand_expr() {
  static char tmp[65536] = {};
  ++ countN;
  if (countN > 10) {
    sprintf(tmp, "%d" , rand() % 50 + 1);
    gen(tmp);
    return;
  }
  switch (rand() % 3) {
  case 0:
    sprintf(tmp, "%d" , rand() % 50 + 1);
    gen(tmp);
    break;
  case 1:
    gen("(");
    gen_rand_expr();
    gen(")");
    break;
  case 2:
    gen_rand_expr();
    gen(opt[rand() % 4]);
    gen_rand_expr();
    break;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    rind = 0;
    countN = 0;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.cpp", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("g++ -w /tmp/.code.cpp -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    if (fscanf(fp, "%d", &result) == 1) {
      printf("%u %s\n", result, buf);
    }
    pclose(fp);

    //printf("%u %s\n", result, buf);
  }
  return 0;
}
