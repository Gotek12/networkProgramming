import java.io.*;
import java.net.*;

class Start2{

    public static void main(String[] args) throws IOException{
        if(args.length != 2) {
            System.out.printf("Bledna ilosc argumetow");
        }
        
        Socket soc = new Socket(args[0], Integer.parseInt(args[1]));
        
        InputStream is;
        int l;
        byte[] bRes = new byte[100];

        try{
            is = soc.getInputStream();
            while((l = is.read(bRes)) != -1){
                //l = is.read(bRes);
                System.out.println(new String(bRes,0,l));
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
  
        soc.close();
         
    }
}