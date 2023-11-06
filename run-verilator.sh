#!/bin/sh

if [ ! -f verilog/verilator/obj_dir/VTop ]; then
    echo "Failed to generate Verilog"
    exit 1
fi

verilog/verilator/obj_dir/VTop $*
