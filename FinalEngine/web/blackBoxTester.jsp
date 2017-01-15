<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import="java.io.*,engineSources.*,org.apache.commons.fileupload.servlet.ServletFileUpload" %>

<%! String path="D:\\EngineTest\\FinalEngine\\sandbox\\blackBoxTester\\";%>
<%! String cppName,inputName,result="result.txt"; %>

<%
    if(ServletFileUpload.isMultipartContent(request))
    {  
        cppName="Code.cpp";
        inputName="TestIn.txt";
        
        UploaderClass obj=new UploaderClass();
        obj.doUP(request, path);
    }       
    else if(request.getParameter("codeArea")==null)
    {
        cppName="DefaultCode.cpp";
        inputName="DefaultInput.txt";

        CmdRunner.blackBoxCmd(path,cppName,inputName,result);
    }
    else
    {
        cppName="Code.cpp";
        inputName="TestIn.txt";
        FileWriter ofile=new FileWriter(path+"Code.cpp");
        ofile.write(request.getParameter("codeArea"));
        ofile.close();
        ofile=new FileWriter(path+"TestIn.txt");
        ofile.write(request.getParameter("inputArea")+"\r\n");
        ofile.close();
 
        CmdRunner.blackBoxCmd(path,cppName,inputName,result);
    }
    
%>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="shortcut icon" href="assets/ico/favicon.ico">

    <!-- Bootstrap core CSS -->
    <link href="css/bootstrap.css" rel="stylesheet">

    <link rel="stylesheet" type="text/css" href="plugin/codemirror/lib/codemirror.css">
    <script type="text/javascript" src="plugin/codemirror/lib/codemirror.js"></script>
    <script type="text/javascript" src="js/jquery.min.js"></script>
    <script src="plugin/codemirror/addon/edit/matchbrackets.js"></script>
    <link rel="stylesheet" href="plugin/codemirror/addon/hint/show-hint.css">
    <script src="plugin/codemirror/addon/hint/show-hint.js"></script>

    <script src="plugin/codemirror/addon/search/search.js"></script>
    <script src="plugin/codemirror/addon/search/searchcursor.js"></script>
    <script src="plugin/codemirror/addon/search/jump-to-line.js"></script>
    <script src="plugin/codemirror/addon/dialog/dialog.js"></script>
    <script src="plugin/codemirror/addon/dialog/dialog.css"></script>

    <script src="plugin/codemirror/mode/clike/clike.js"></script>
    <style>.CodeMirror {border: 1px solid #b8b8b8;}</style>

    <link href="css/font-awesome.min.css" rel="stylesheet">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <style type='text/css'>
    </style>
    <title>AnalysisEngine</title>
    <link rel="stylesheet" href="css/global.css">

</head>

<body data-spy="scroll" data-target=".navbar" data-offset="50">

    <!-- Static navbar -->
    <div class="navbar navbar-default navbar-fixed-top" role="navigation">
        <div class="container">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                
                <a class="navbar-brand" href="index.html" id="logoText">AnalysisEngine</a>
            </div>
            <div class="navbar-collapse collapse">
                <ul class="nav navbar-nav navbar-right" id="menulist">
                    <li ><a href="http://localhost:8080/FinalEngine/compiler.jsp">Compiler</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/codeFormatter.jsp">Formatter</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/codeReporter.jsp">Reporter</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/codeTime.jsp">TimeTool</a>
                    </li>
                    <li class="active"><a href="http://localhost:8080/FinalEngine/blackBoxTester.jsp">BlackBoxTester</a>
                    </li>
                </ul>
            </div>
            <!--/.nav-collapse -->
        </div>
    </div>

    <div class="container heading ">
        <div class="col-md-4">
            <h1>Black Box Tester</h1>
        </div>
    </div>

    <div class="container">
        <div class="col-md-12 boxSection">            
            <p>
                <div class="col-md-12">
                    <div class="col-md-6 greyBox">
                        <form action="blackBoxTester.jsp" method="post" ENCTYPE="multipart/form-data">
                            <div class="col-md-1"><h4 style="color:black;font-size:20px;">Code:-</h4></div>
                                <div class="col-md-4 margin-top-10 margin-left-25">
                                    <input type="file" name="file" />
                                </div>
                                <div class=" col-md-2 margin-left-25  margin-bottom-10">
                                    <button type="submit" class="btn btn-primary ">
                                        <i class="fa fa-upload" aria-hidden="true"></i> Upload
                                    </button>
                                </div>

                        </form>
                        
                        <div class="col-md-3 margin-left-25 margin-bottom-10">
                            <form action="DownloaderServlet">
                                <input type="hidden" name="filepath" value=<%=path%>>
                                <input type="hidden" name="filename" value="Code.cpp">
                                <input type="hidden" name="downloadName" value="SourceCode.cpp">
                                <button type="submit" class="btn btn-success ">
                                    <i class="fa fa-download icon-black" aria-hidden="true"></i> Download
                                </button>
                            </form>
                        </div>
                    </div>
                    
                    <div class="col-md-6 greyBox">
                        <label class="enterCode" for="code">Output :-</label>

                        <form class="outButton" action="DownloaderServlet">
                            <input type="hidden" name="filepath" value=<%=path%>>
                            <input type="hidden" name="filename" value="result.txt">
                            <input type="hidden" name="downloadName" value="Output.txt">
                            <button type="submit" class="btn btn-success ">
                                <i class="fa fa-download icon-black" aria-hidden="true"></i> Download
                            </button>
                        </form>
                    </div>
                </div>
            
                <form action="blackBoxTester.jsp" method="post" target="_parent">
                    <div class="col-md-12">
                        <div class="col-md-6">
                            <textarea class="leftTextarea" id="code" name="codeArea" rows="20" cols="70"><% 
                                FileReader ifile=new FileReader(path+cppName);
                                int i;
                                while((i=ifile.read())!=-1)
                                {
                                    out.print(String.valueOf((char)i));
                                }
                                ifile.close();
                            %></textarea>
                        </div>
                        <div class="col-md-6">
                            <textarea class="rightTextarea" id="output" rows="20" cols="70"><% 
                                ifile=new FileReader(path+result);
                                
                                while((i=ifile.read())!=-1)
                                {
                                    out.print(String.valueOf((char)i));
                                }
                                ifile.close();
                            %></textarea>
                        </div>
                    </div>

                    <div class="col-md-6">
                        <div class="col-md-8">
                            <textarea class="lasttextarea" id="input" name="inputArea" rows="10" cols="70"><% 
                                ifile=new FileReader(path+inputName);
                                
                                while((i=ifile.read())!=-1)
                                {
                                    out.print(String.valueOf((char)i));
                                }
                                ifile.close();
                            %></textarea>
                        </div>
                        <div class="col-md-4">
                            <!--<div class="formatButton">-->
                            <!--<input type="submit" class="btn btn-primary btn-lg" value="Format" name="check" />-->
                            <!--</div>-->
                            <button type="submit" class="btn btn-success margin-left-60 margin-top-30">    
                            <i class="fa fa-caret-square-o-right" aria-hidden="true" name="check"></i> RunTest
                            </button>
                        </div>
                    </div>
                </form>
            </p>
        </div>

    </div>
    <div class="container inputBox">

    </div>

    <script>

      var cppEditor = CodeMirror.fromTextArea(document.getElementById("code"), {
        lineNumbers: true,
        matchBrackets: true,
        mode: "text/x-c++src"
      });
      cppEditor.setSize(500, 424);
      var cppEditor = CodeMirror.fromTextArea(document.getElementById("output"), {
      matchBrackets: true,
      mode: "text/x-c++src"
      });
      cppEditor.setSize(515, 424);
      
      var mac = CodeMirror.keyMap.default == CodeMirror.keyMap.macDefault;
      CodeMirror.keyMap.default[(mac ? "Cmd" : "Ctrl") + "-Space"] = "autocomplete";
    </script>
    
    <script src="js/bootstrap.min.js"></script>
    </script>


</body>
</html>