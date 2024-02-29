import java.net.*;
import java.io.*;

public class server {
    public static void main(String[] args){
        try (ServerSocket serverSocket = new ServerSocket(6052)){
            System.out.println("Server is listening to port 6052");

            while (true) {
                Socket socket = serverSocket.accept();
                new ServerThread(socket).start();
            }
        }catch (IOException e) {
            System.out.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }        
    }
}


class ServerThread extends Thread {
    private Socket socket;

    public ServerThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try{
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            String hostname = reader.readLine();
            try {
                InetAddress hostAddress = InetAddress.getByName(hostname);
                String IPaddress = hostAddress.getHostAddress();
                writer.println("\033[34m" + IPaddress + "\033[1m");
            } catch(UnknownHostException e) {
                writer.println("\033[34mUnable to resolve host " + hostname + "\033[1m");
            } finally {
                socket.close();
            }
        } catch (IOException e) {
            System.out.println("Server thread exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}