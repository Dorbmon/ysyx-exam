#include <isa.h>
#include <memory/vaddr.h>
#include <memory/paddr.h>
#include <memory/host.h>
extern word_t csrM[];
#define ext2(x, s, t) ((x >> s) & ((1ull << (t - s + 1)) - 1))
int isa_mmu_check(vaddr_t vaddr, int len, int type) {
  uint64_t satp = csrM[0x180];
  if (satp & (1ull << 63)) {
    //printf("shit\n");
  }
  return satp >> 63 == 1;
}
paddr_t isa_mmu_translate(vaddr_t vaddr, int len, int type) {
  if (!isa_mmu_check(vaddr, len, type)) {
    return vaddr;
  }
  //printf("tran:%lx\n", vaddr);
  // 开始转换
  // 读取第一层表地址
  uint64_t satp = csrM[0x180];
  uint64_t table1 = satp << 12;
  size_t l1 = ext2((size_t)vaddr, 30, 38), l2 = ext2((size_t)vaddr, 21, 29), l3 = ext2((size_t)vaddr, 12, 20);
  // 开始依次读取
  //printf("first....\n");
  uint64_t t3 = host_read(guest_to_host(table1 + l1 * 8), 8);
  // 提取地址
  uint64_t addr = ext2(t3, 10, 47);
  // 接着访问这一层
  addr <<= 12;
  addr += l2 * 8;
  if ((uint64_t)guest_to_host(addr) == 0x5554d56b7000) {
    printf("vaddr:%lx\n", vaddr);
  }
  t3 = host_read(guest_to_host(addr), 8);
  addr = ext2(t3, 10, 47);
  // 接着访问这一层
  addr <<= 12;
  addr += l3 * 8;
  t3 = host_read(guest_to_host(addr), 8);
  addr = ext2(t3, 10, 47);
  uint64_t res = (addr << 12) + ext2(vaddr, 0, 11);
  return res;
}
