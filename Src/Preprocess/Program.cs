using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Preprocess
{
    class Program
    {
        static void Main(string[] args)
        {
               StreamReader sm = new StreamReader(@"C:\Users\liaojian\Desktop\e.txt");
               StreamWriter sw = new StreamWriter(@"C:\Users\liaojian\Desktop\e_1.txt");
               while (!sm.EndOfStream)
               {
                   string line = sm.ReadLine();
                   int length = line.Length;
                   if (length > 2)
                   {
                
                       sw.WriteLine(line);
                   }
                   
               }
               sm.Close();
               sw.Close();
            string s = "\n";
            Console.WriteLine(s.Length);
        }
    }
}
