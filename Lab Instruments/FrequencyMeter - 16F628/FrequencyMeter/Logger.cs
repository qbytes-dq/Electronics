using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;


namespace WFF_Generic_HID_Demo_3//QBW.Magic.LED
{
    public class Logger
    {
        public enum LogLevels { Debug = 1, Info = 2, Warn = 3, Error = 4 };
        public static LogLevels logLevel = LogLevels.Debug;

        private static string sPathName = @".\logs\";
        private static string sFileName = "magicLed.";
        private static string sLogFormat;
        private static string sErrorTime;

        private static object oLock = new object();

        public static void Write(LogLevels level, string sErrMsg)
        {

            lock (oLock)
            {
                if (sErrMsg != null && sErrMsg.Length > 0)
                {
                    if (level.CompareTo(logLevel) >= 0)
                    {
                        CreateLogPath();

                        CreateFileVars();

                        StreamWriter sw = new StreamWriter(sPathName + sErrorTime, true);
                        sw.WriteLine(sLogFormat + level.ToString() + " -- " + sErrMsg);
                        sw.Flush();
                        sw.Close();

                        Debug.WriteLine(sErrMsg);
                    }
                }
            }
            // oLock = null;
        }

        private static void CreateLogPath()
        {
            if (!Directory.Exists(sPathName))
                Directory.CreateDirectory(sPathName);
        }

        private static void CreateFileVars()
        {
            //sLogFormat used to create log files format
            // dd/mm/yyyy hh:mm:ss AM/PM ==> Log Message
            sLogFormat = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss.fff ::: ");

            //this variable used to create log filename format
            string sLogNameFormat = DateTime.Now.ToString("yyyyMMdd");
            sErrorTime = sFileName + sLogNameFormat + ".log";
        }
    }
}