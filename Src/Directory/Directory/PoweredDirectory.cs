using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Win32;
using System.Diagnostics;

namespace Directory
{
    public static class PoweredDirectory
    {
        static PoweredDirectory()
        {
            
        }

        /// <summary>
        /// 讲一个目录拷贝到另一个目录
        /// </summary>
        /// <param name="srcPath">待拷贝的目录名</param>
        /// <param name="dstPath">目标目录名</param>
        /// <param name="overWrite">同名文件是否要覆写，true表示覆写</param>
        public static void Copy(string srcPath,string dstPath, bool overWrite)
        {
            DirectoryInfo srcDir = new DirectoryInfo(srcPath);
            DirectoryInfo dstDir = new DirectoryInfo(dstPath);
            if (!srcDir.Exists) throw new ArgumentException("不合法的原文件路径！");
            if (!dstDir.Exists)
            {
                try
                {
                    dstDir.Create();
                }
                catch(Exception ex)
                {
                    throw ex;
                }
            }
            dstDir = dstDir.CreateSubdirectory(srcDir.Name);
            FileInfo[] files = srcDir.GetFiles();
            foreach (FileInfo f in files)
            {
                File.Copy(f.FullName, dstDir.FullName + "\\" + f.Name,overWrite);
            }
            DirectoryInfo[] dirs = srcDir.GetDirectories();
            foreach (DirectoryInfo d in dirs)
            {
                Copy(d.FullName, dstDir.FullName,overWrite);
            }
        }

        public static void CompressToRAR(string dirPath, string dstFileName)
        {
            try
            {
                RegistryKey reg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\MICROSOFT\WINDOWS\CurrentVersion\App Paths\WinRAR.exe");
                string winRARPath = reg.GetValue("").ToString();
                reg.Close();
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.FileName = winRARPath;
                DirectoryInfo dirinfo = new DirectoryInfo(dirPath);
                string dirParentPath = dirinfo.Name;
                startInfo.Arguments = "a " + dstFileName + " \"" + dirParentPath + "\" -r";
                startInfo.WindowStyle = ProcessWindowStyle.Minimized;
                startInfo.WorkingDirectory = dirinfo.Parent.FullName;
                Process winrarPro = new Process();
                winrarPro.StartInfo = startInfo;
                winrarPro.Start();
                winrarPro.WaitForExit();
                winrarPro.Close();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
