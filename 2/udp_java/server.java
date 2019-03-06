import java.io.*;
import java.net.*;

class Server{

    public static void main(String[] args) throws IOException{
        if(args.length != 1) {
            System.out.printf("Bledna ilosc argumetow");
        }
        
        String komunikat = "Hello, world!\r\n";
        DatagramSocket soc = new DatagramSocket(Integer.parseInt(args[0]));
        byte[] buf = new byte[256];

        while(true){
            System.out.printf("Waiting for conection ...\n");

            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            soc.receive(packet);

            InetAddress address = packet.getAddress();
            int port = packet.getPort();

            buf = komunikat.getBytes();
            packet = new DatagramPacket(buf, buf.length, address, port);

            soc.send(packet);
            System.exit(1);
        }

        //soc.close();
    }
}