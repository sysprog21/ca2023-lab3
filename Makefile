.PHONY: test verilator

test:
	sbt test

verilator:
	sbt "runMain board.verilator.VerilogGenerator"
	cd verilog/verilator && verilator --trace --exe --cc sim_main.cpp Top.v && make -C obj_dir -f VTop.mk

indent:
	find . -name '*.scala' | xargs scalafmt
	clang-format -i verilog/verilator/*.cpp
	clang-format -i csrc/*.[ch]
