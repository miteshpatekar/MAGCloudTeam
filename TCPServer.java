import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {

	public static void main(String[] args) throws Exception {
		ServerSocket s = null;
		Socket conn = null;
		DataInputStream dis=null;
		//1. creating a server socket - 1st parameter is port number and 2nd is the backlog
		s = new ServerSocket(5001 , 10);
		//2. Wait for an incoming connection
		System.out.println("Server socket created. Waiting for connection...");
		//get the connection socket
		conn = s.accept();
		//print the hostname and port number of the connection
		System.out.println("Connection received from " + conn.getInetAddress().getHostName() + " : " + conn.getPort());
		// Socket sock = new Socket(server, 43);
		int c = 0;

		OutputStream os = conn.getOutputStream();
		InputStream is = conn.getInputStream();
		// create data input stream
		dis = new DataInputStream(is);
		int count=0;
		// readBoolean till the data available to read
		while( dis.available() >0)
		{
			// read one single byte
			byte b = dis.readByte();   
			// print the byte
			System.out.print((char)b+" ");
			count+=1;
		}
		String ack="y";
		System.out.println("No. of bytes transferred= "+count);
		os.write(ack.getBytes("iso8859_1"));
	}
}
