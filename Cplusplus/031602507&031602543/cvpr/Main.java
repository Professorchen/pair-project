import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private static String URL = "http://openaccess.thecvf.com/CVPR2018.py";

    public static void main(String[] args) throws IOException {
        System.out.println("Running,about 3 minutes");
        PaperProcess(GetData(URL));//Processing 
        System.out.println("Finished!");
    }

    public static String GetData(String urlString) throws IOException {
        URL url = new URL(urlString);
        HttpURLConnection huc = (HttpURLConnection) url.openConnection();//send request

        huc.setDoInput(true);
        huc.setRequestMethod("GET");
        
        InputStream in = huc.getInputStream();
        InputStreamReader inReader = new InputStreamReader(in, "UTF-8");//read http flow
        BufferedReader Bf = new BufferedReader(inReader);
        StringBuilder str = new StringBuilder();// read data into str
        String current = null;
        while ((current = Bf.readLine()) != null) {//read data and stored
            str.append(current);
        }
        Bf.close(); /* close connection and input stream */
        inReader.close();
        in.close();
        huc.disconnect();
        return (str.toString());
    }


    public static void PaperProcess(String html) throws IOException {
        Pattern pattern = Pattern.compile("<dt class=\"ptitle\"><br><a href=\"([^\"]*)\">([^<]*)");// data is stored in the middle of dt class="ptitle">
        Matcher matcher = pattern.matcher(html);
        File fp = new File("result.txt");

        if (fp.exists()) fp.createNewFile();

        PrintWriter printWriter = new PrintWriter(
                new OutputStreamWriter(new FileOutputStream(fp), "UTF-8"));

        int paperNumber = 0;
        while (matcher.find()) {
            
            String Abstract = GetAbstract("http://openaccess.thecvf.com/" + matcher.group(1));//Abstract
            printWriter.println(paperNumber);//title
            printWriter.println("Title: " + matcher.group(2));//Abstract
            printWriter.println("Abstract: " + Abstract);//use two \n to devine two papers 
            printWriter.println();
            printWriter.println();

            System.out.print("The " + String.valueOf(paperNumber) + " paper is finished\r");

            paperNumber += 1;
        }
        System.out.println();
        printWriter.flush();
        printWriter.close();
    }

    public static String GetAbstract(String paperURL) throws IOException {
        String paperHtml = GetData(paperURL);
        Pattern pattern = Pattern.compile("<div id=\"abstract\" >(.*?)</div>");
        Matcher m = pattern.matcher(paperHtml);
        if (m.find()) {
            return m.group(1);
        }
        return null;
    }
}
