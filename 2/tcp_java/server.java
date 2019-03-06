import java.io.*;
import java.net.*;

class Start{

    public static void main(String[] args) throws IOException{
        if(args.length != 1) {
            System.out.printf("Bledna ilosc argumetow");
        }
        
        String komunikat = "Hello, world!\r\n";

        ServerSocket soc = new ServerSocket(Integer.parseInt(args[0]));
        Socket ac;

        while(true){
            System.out.printf("Waiting for conection ...\n");
            ac = soc.accept();
            
            //send welkome
            OutputStream output = ac.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);
            writer.println(komunikat);

            System.out.printf("Wyslano\n");

            ac.close();
            System.exit(1);
        }     
    }
}