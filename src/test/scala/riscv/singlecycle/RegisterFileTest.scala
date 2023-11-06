// mycpu is freely redistributable under the MIT License. See the file
// "LICENSE" for information on usage and redistribution of this file.

package riscv.singlecycle

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import riscv.core.RegisterFile
import riscv.TestAnnotations

class RegisterFileTest extends AnyFlatSpec with ChiselScalatestTester {
  behavior.of("Register File of Single Cycle CPU")
  it should "read the written content" in {
    test(new RegisterFile).withAnnotations(TestAnnotations.annos) { c =>
      timescope {
        c.io.write_enable.poke(true.B)
        c.io.write_address.poke(1.U)
        c.io.write_data.poke(0xdeadbeefL.U)
        c.clock.step()
      }
      c.io.read_address1.poke(1.U)
      c.io.read_data1.expect(0xdeadbeefL.U)
    }
  }

  it should "x0 always be zero" in {
    test(new RegisterFile).withAnnotations(TestAnnotations.annos) { c =>
      timescope {
        c.io.write_enable.poke(true.B)
        c.io.write_address.poke(0.U)
        c.io.write_data.poke(0xdeadbeefL.U)
        c.clock.step()
      }
      c.io.read_address1.poke(0.U)
      c.io.read_data1.expect(0.U)
    }
  }

  it should "read the writing content" in {
    test(new RegisterFile).withAnnotations(TestAnnotations.annos) { c =>
      timescope {
        c.io.read_address1.poke(2.U)
        c.io.read_data1.expect(0.U)
        c.io.write_enable.poke(true.B)
        c.io.write_address.poke(2.U)
        c.io.write_data.poke(0xdeadbeefL.U)
        c.clock.step()
        c.io.read_address1.poke(2.U)
        c.io.read_data1.expect(0xdeadbeefL.U)
        c.clock.step()
      }
      c.io.read_address1.poke(2.U)
      c.io.read_data1.expect(0xdeadbeefL.U)
    }
  }

}
