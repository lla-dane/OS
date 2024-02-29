import java.net.*;
import java.io.*;

public class client {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java client <hostname>");
            return;
        }

        String hostname = args[0];
        try (Socket socket = new Socket("localhost", 6052)) {
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            writer.println(hostname);

            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            String response = reader.readLine();
            // ANSI escpae code for blue output
            System.out.println("\033[34m" + response + "\033[1m");
        }catch (UnknownHostException ex) {
            System.out.println("Server not found: " + ex.getMessage());
        }catch(IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
        }
    }
}