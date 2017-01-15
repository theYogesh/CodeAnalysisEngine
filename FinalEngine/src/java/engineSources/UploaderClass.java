package engineSources;

import java.io.File;
import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class UploaderClass extends HttpServlet
{
    public int doUP(HttpServletRequest request,String path)
            throws ServletException, IOException 
    {  
        //process only if its multipart content
        if(ServletFileUpload.isMultipartContent(request))
        {
            try {
                List<FileItem> multiparts = new ServletFileUpload(
                                         new DiskFileItemFactory()).parseRequest(request);
              
                for(FileItem item : multiparts)
                {
                    if(!item.isFormField())
                    {
                        String name = "Code.cpp";
                                //new File(item.getName()).getName();
                        item.write( new File(path + File.separator + name));
                    }
                }
            } 
            catch (Exception ex)
            {
               return 0;
            }          
        }
        else
        {
            return 0;
        }
        return 1;
    }
}
