#include <assert.h>
#include "debug.h"
#include <stdint.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include "expr.h"
enum {
  TK_NOTYPE = 256,
  TK_EQ,
  TK_DEREF,
  TK_NEG,
  TK_REG,
  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
  int level;
} rules[] = {

    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */
    {"==", TK_EQ, 0},                                              // equal
    {"[(]", '(', 1},           {"[)]", ')', 1}, {" +", TK_NOTYPE}, // spaces
    {"\\+", '+', 2},                                               // plus
    {"\\-", '-', 2}, // 十进制数字
    {"\\\\", '\\', 3},         {"\\*", '*', 3}, {"\\$([0-9a-zA-Z]+) ", TK_REG, 4},{"\\$([0-9a-zA-Z]+)", TK_REG, 4},
    {"0x[0-9a-fA-F]+", 'n', 4}};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}
#define MAX_TOKEN_NUM 60
typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[MAX_TOKEN_NUM] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 &&
          pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i,
        //     rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;
        switch (rules[i].token_type) {
        case TK_NOTYPE:
          // 抛弃空格
          break;
        case 'n':
          memcpy(tokens[nr_token].str, substr_start,
                 substr_len); //要拷贝 '/0'
        case TK_REG:
          memcpy(tokens[nr_token].str, substr_start,substr_len);
        default:
          tokens[nr_token].type = rules[i].token_type;
          nr_token++;
        }
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}
uint32_t eval(int p, int q);
void removeToken(int index) {
  static Token tmp[MAX_TOKEN_NUM];
  memcpy(tmp, tokens, sizeof(Token) * index);
  memcpy(tmp + index, tokens + index + 1,
         sizeof(Token) * (MAX_TOKEN_NUM - index - 1));
  nr_token--;
  memcpy(tokens, tmp, sizeof(tmp));
}
bool isS(char c) {
  return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') ||
         (c == ')');
}
uint32_t expr(char *e, bool *success) {
  *success = true;
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '*' && (i == 0 || tokens[i - 1].type == 'n')) {
      tokens[i].type = TK_DEREF;
    }
    if (tokens[i].type == '-' && (i == 0 || isS(tokens[i - 1].type))) {
      tokens[i].type = TK_NEG;
    }
  }
  // 执行表达式
  return eval(0, nr_token - 1);
}
bool check_parentheses(int p, int q, bool *fail) {
  if (!(tokens[p].type == '(' && tokens[q].type == ')')) {
    return false;
  }
  // 然后检查括号是否配对
  int pN = 0;
  for (int i = p; i <= q; ++i) {
    if (tokens[i].type == '(')
      pN++;
    if (tokens[i].type == ')')
      pN--;
    if (pN < 0) {
      *fail = true;
      return false;
    }
  }
  return true;
}
uint32_t eval(int p, int q) {
  printf("%d %d\n", p, q);
  Assert(p <= q, "error sequence %d", p);
  bool fail = false;
  if (p + 1 == q) {
    if (tokens[p].type == TK_NEG) {
      uint32_t v = -eval(p + 1, q);
      // printf("%d %d %d\n", p, q, v);
      return v;
    }
    if (tokens[p].type == TK_DEREF) {
      bool success;
      printf("reg:%s;\n", tokens[q].str);
      int ind = strlen(tokens[q].str) - 1;
      while (ind > 0) {
        if (tokens [q].str[q] == ' ') {
          tokens [q].str[q] = '\0';
        } else {
          break;
        }
      }
      word_t value = isa_reg_str2val(tokens[q].str, &success);
      assert(success);
      return value;
    }
  } else if (p == q) {
    Assert(tokens[p].type == 'n', "It should be a number istead of %d",
           tokens[p].type);
    uint64_t value;
    sscanf(tokens[p].str, "%lx", &value);
    return value;
  } else if (check_parentheses(p, q, &fail) == true && !fail) {
    return eval(p + 1, q - 1);
  } else if (fail) {
    Assert(0, "load failed %s", "dead");
  } else {
    /* We should do more things here. */
    int pLevel = 0; //括号嵌套深度
    int nowLow = 100;
    int position = -1;
    for (int i = p; i <= q; ++i) {
      if (tokens[i].type == '(')
        pLevel++;
      else if (tokens[i].type == ')')
        pLevel--;
      else if (pLevel == 0) {
        for (int j = 0; j < NR_REGEX; ++j) {
          if (tokens[i].type == rules[j].token_type) {
            if (position == -1) {
              position = i;
            } else if (nowLow >= rules[j].level) {
              position = i;
              nowLow = rules[j].level;
            }
          }
        }
      }
    }
    uint32_t val1 = eval(p, position - 1);
    uint32_t val2 = eval(position + 1, q);

    switch (tokens[position].type) {
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      return val1 / val2;
    default:
      Assert(0, "Unknown Opt: %c", tokens[position].type);
    }
  }
  return 0;
}