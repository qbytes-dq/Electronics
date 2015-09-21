using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics; // 1

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {

            Debug.WriteLine("\n\n http://www.rfcandy.biz/communication/lc.html#jmp\n");

            double f1, f2, c, l,  lx, lk, cx, fn1, fn2, fn3, fn4, fn5;

            // Fixed Cap math
            //    Milla
            //       Micro
            //          Nano
            //             Pico
            //    mmmuuunnnppp
            c = 0.000001000; // 1uF, 1,000nF or 1,000,000pF

            //l = 0.000068; // 68 uH
            l = 0.000100; // 100uH


            double exp = 2 * 3.14;
            double pow2 = Math.Pow(exp, 2);
            double cpow = c * pow2;
            double cap = 1 / cpow;

            // *****************************************//
            // Unknown Lx
            // *****************************************//
            // Fixed inductor
            f1 = 500500; // 100u @ 2.43v

            f2 = 353435; // 100u 
            f2 = 290000; // 200u
            f2 = 242626; // 300u
            
            
            f1 = 1/Math.Pow(f1, 2);
            f2 = 1/Math.Pow(f2, 2);

            Debug.WriteLine("\nSolve for Lx");

            lk = cap * f1; // Known coil

            lx = cap * (f2-f1); // Un-known coil

            Debug.WriteLine(lk.ToString("0.000 000 000 000"));
            Debug.WriteLine(lx.ToString("0.000 000 000 000"));
            Debug.WriteLine("0.mmm uuu nnn ppp\n\n");
            // *****************************************//
            // Unknown Cx
            // *****************************************//

            f1 = 610331; // 1u or 1,000p

            f2 = 508609; // 440p
            f2 = 425500; // 1,000p
            f2 = 343000; // 2,000p
            f2 = 129572; // 20,000p

            fn1 = (f1 / f2);
            fn2 = Math.Pow(fn1, 2);
            fn3 = fn2 - 1d;
            cx = fn3 * c;
            Debug.WriteLine("\nSolve for Cx");
            Debug.WriteLine(cx.ToString("0.000 000 000 000"));
            Debug.WriteLine("0.mmm uuu nnn ppp\n\n");
        }
    }
}
