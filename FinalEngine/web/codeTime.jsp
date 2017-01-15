<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page import="java.io.*,engineSources.*,org.apache.commons.fileupload.servlet.ServletFileUpload" %>

<%! String path="D:\\EngineTest\\FinalEngine\\sandbox\\codeTime\\";%>
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
 
        CmdRunner.timeCmd(path,cppName,inputName,request.getParameter("iterations"),result);
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
    <link href="css/font-awesome.min.css" rel="stylesheet">

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

    <!-- Just for debugging purposes. Don't actually copy this line! -->
    <!--[if lt IE 9]><script src="../../assets/js/ie8-responsive-file-warning.js"></script><![endif]-->

    <!-- HTML5 shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
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
                
                <a class="navbar-brand" id="logoText" href="index.html">AnalysisEngine</a>
            </div>
            <div class="navbar-collapse collapse">
                <ul class="nav navbar-nav navbar-right" id="menulist">
                    <li><a href="http://localhost:8080/FinalEngine/compiler.jsp">Compiler</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/codeFormatter.jsp">Formatter</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/codeReporter.jsp">Reporter</a>
                    </li>
                    <li class="active"><a href="http://localhost:8080/FinalEngine/codeTime.jsp">TimeTool</a>
                    </li>
                    <li><a href="http://localhost:8080/FinalEngine/blackBoxTester.jsp">BlackBoxTester</a>
                    </li>
                </ul>
            </div>
            <!--/.nav-collapse -->
        </div>
    </div>

    <div class="container heading ">
        <div class="col-md-4">
            <h1>Timer</h1>
        </div>
    </div>

    <div class="container">
        <div class="col-md-12 boxSection">
            <label class="col-md-5 enterCode verticalFirst" for="code">Enter Code :-</label>
            <div class="col-md-5 choseFile verticalFirst">
                
                <form action="codeTime.jsp" method="post" ENCTYPE="multipart/form-data">
                    <div class="col-md-5 margin-top-10 margin-left-25 verticalFirst">
                        <input type="file" name="file" />
                    </div>
                    <div class=" col-md-3 margin-left-25  margin-bottom-10 verticalFirst">
                        <input type="submit" class="btn btn-default" value="Upload Code" name="uploader" />
                    </div>
                </form>
            </div>
            <div class="col-md-2 verticalFirst">
                
                <form action="DownloaderServlet">
                    <input type="hidden" name="filepath" value=<%=path%>>
                    <input type="hidden" name="filename" value="Code.cpp">
                    <input type="hidden" name="downloadName" value="SourceCode.cpp">
                    <input class="srcButton btn btn-success" type="Submit" name="button" value="Download SourceCode">
                </form>

            </div>
        </div>
        
        <form action="codeTime.jsp" method="post" target="_parent">
            <div class="col-md-12 inputAreaTime">
                <textarea class="rightTextarea timeText" name="codeArea" id="code" rows="20" cols="155"><% 
                    FileReader ifile=new FileReader(path+cppName);
                    int i;
                    while((i=ifile.read())!=-1)
                    {
                        out.print(String.valueOf((char)i));
                    }
                    ifile.close();
                %></textarea>
            </div>
    </div>

    <div class="container inputBoxTime">
        <div class="col-md-6">
            <textarea class="rightTextareaTime" name="inputArea" id="input" rows="10" cols="70"><% 
                ifile=new FileReader(path+inputName);
                  
                while((i=ifile.read())!=-1)
                {
                    out.print(String.valueOf((char)i));
                }
                ifile.close();
            %></textarea>
        </div>
        <div class="col-md-6">
            <div class="col-md-6">
                <input type="number" class="iterationInput" name="iterations" min="100" max="1000" value="200" required/>
            </div>
            <div class="col-md-6">
                <div class="formatButton">
                    <input type="submit" class="btn btn-primary btn-lg" value="CalculateTime" name="check" />
                </div>
            </div>
        </div>
        <div class="col-md-6">
            <textarea class="finalTextareaTime" id="output" rows="1" cols="25" readonly><%  
                if(!cppName.equals("DefaultCode.cpp"))
                {
                    ifile=new FileReader(path+"result.txt");
                    while((i=ifile.read())!=-1)
                    {
                        out.print(String.valueOf((char)i));
                    }
                }
            %></textarea>
        </div>
    </div>

    </form>

    <script>

      var cppEditor = CodeMirror.fromTextArea(document.getElementById("code"), {
        lineNumbers: true,
        matchBrackets: true,
        mode: "text/x-c++src"
      });
      cppEditor.setSize(1100, 500);
      
      var mac = CodeMirror.keyMap.default == CodeMirror.keyMap.macDefault;
      CodeMirror.keyMap.default[(mac ? "Cmd" : "Ctrl") + "-Space"] = "autocomplete";
    </script>


    <script src="js/bootstrap.min.js"></script>
    </script>

</body>
</html>