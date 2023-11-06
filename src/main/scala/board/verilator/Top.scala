// mycpu is freely redistributable under the MIT License. See the file
// "LICENSE" for information on usage and redistribution of this file.

package board.verilator

import chisel3._
import chisel3.stage.ChiselGeneratorAnnotation
import chisel3.stage.ChiselStage
import peripheral._
import riscv.core.CPU
import riscv.CPUBundle
import riscv.Parameters

class Top extends Module {
  val io = IO(new CPUBundle)

  val cpu = Module(new CPU)

  io.deviceSelect           := 0.U
  cpu.io.debug_read_address := io.debug_read_address
  io.debug_read_data        := cpu.io.debug_read_data

  io.memory_bundle <> cpu.io.memory_bundle
  io.instruction_address := cpu.io.instruction_address
  cpu.io.instruction     := io.instruction

  cpu.io.instruction_valid := io.instruction_valid
}

object VerilogGenerator extends App {
  (new ChiselStage)
    .execute(Array("-X", "verilog", "-td", "verilog/verilator"), Seq(ChiselGeneratorAnnotation(() => new Top())))
}
