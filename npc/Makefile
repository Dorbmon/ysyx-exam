all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wall --cc --trace --coverage --assert --exe --f vsrc/input.vc csrc/main.cpp vsrc/top.v
	make -j -C obj_dir -f Vtop.mk
	obj_dir/Vtop
	gdkwave data.vcd
include ../Makefile
