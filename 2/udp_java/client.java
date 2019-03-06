import java.io.*;
import java.net.*;

class Client{

    public static void main(String[] args) throws IOException{
        if(args.length != 2) {
            System.out.printf("Bledna ilosc argumetow");
        }
        
        DatagramSocket soc = new DatagramSocket();
        InetAddress address = InetAddress.getByName(args[0]);
        byte[] buf = new byte[1024];
        byte[] sendData = new byte[1024];
        
        String ko = "test";
        sendData = ko.getBytes();

        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, address, Integer.parseInt(args[1]));
        soc.send(sendPacket);

        DatagramPacket receivePacket = new DatagramPacket(buf, buf.length);
        soc.receive(receivePacket);

        String modifiedSentence = new String(receivePacket.getData());
        System.out.println(modifiedSentence + "\n");

        soc.close();
    }
}