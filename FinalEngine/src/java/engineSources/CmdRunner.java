package engineSources;

import java.io.*;

public class CmdRunner
{
    public static void formatCmd(String path,String cppName,String result)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"formatCmdBatch.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("set PATH=%PATH%;\"D:\\EngineTest\\FinalEngine\\tools\"; "+"\r\n");
            ofile.write("D:"+"\r\n");
            ofile.write("CodeFormatter "+cppName+" "+result+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"formatCmdBatch.bat").waitFor();
            File file=new File(path+"formatCmdBatch.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
    
    public static void timeCmd(String path,String cppName,String inputName,String iterationCount,String result)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"timeCmdBatch.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("set PATH=%PATH%;\"D:\\EngineTest\\FinalEngine\\tools\"; "+"\r\n");
            ofile.write("D:"+"\r\n");
            ofile.write("timeCmd "+cppName+" "+inputName+" "+iterationCount+" "+result+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"timeCmdBatch.bat").waitFor();
            File file=new File(path+"timeCmdBatch.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
    
    public static void reportCmd(String path,String cppName,String result)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"reportCmdBatch.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("set PATH=%PATH%;\"D:\\EngineTest\\FinalEngine\\tools\"; "+"\r\n");
            ofile.write("D:"+"\r\n");
            ofile.write("reportCmd "+cppName+" "+result+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"reportCmdBatch.bat").waitFor();
            File file=new File(path+"reportCmdBatch.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
    
    public static void compileCmd(String path,String cppName,String inputName,String result)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"compileCmdBatch.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("set PATH=%PATH%;\"D:\\EngineTest\\FinalEngine\\tools\"; "+"\r\n");
            ofile.write("D:"+"\r\n");
            ofile.write("compileCmd "+cppName+" "+inputName+" "+result+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"compileCmdBatch.bat").waitFor();
            File file=new File(path+"compileCmdBatch.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
    
    public static void blackBoxCmd(String path,String cppName,String inputName,String result)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"blackBoxCmdBatch.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("set PATH=%PATH%;\"D:\\EngineTest\\FinalEngine\\tools\"; "+"\r\n");
            ofile.write("D:"+"\r\n");
            ofile.write("blackBoxCmd "+cppName+" "+result+"<"+inputName+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"blackBoxCmdBatch.bat").waitFor();
            File file=new File(path+"blackBoxCmdBatch.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
    
    public static void delBatch(String path)
    {
        try
        {
            FileWriter ofile=new FileWriter(path+"del.bat");
            ofile.write("cd "+path+"\r\n");
            ofile.write("del Code.cpp,TestIn.txt,testOut.txt,result.txt,result.cpp;"+"\r\n");
            ofile.write("exit");
            ofile.close();
            Runtime.getRuntime().exec("cmd.exe /c start /B /wait "+path+"del.bat").waitFor();
            File file=new File(path+"del.bat");
            file.delete();
        }
        catch(Exception e)
        {
        }
    }
}
