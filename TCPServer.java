import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

class ThreadServer implements Runnable {
	private Thread t;
	private String threadName;
	private int blkSize;
	private int port;

	public static int BYTE=1;
	public static int KILOBYTE=1024;
	public static int SIXTYFOURKB=64*1024;

	public static String host = "127.0.0.1";
	public static DataOutputStream dos_out = null;
	public static DataInputStream dis = null;
	public static InputStream is=null;
	public static OutputStream os=null;

	ThreadServer( String name,int portno){
		threadName = name;
		//blkSize = size;
		port=portno;
		System.out.println("Creating " +  threadName );
	}
	
	public void run() {
		System.out.println("Running " +  threadName );
		//try {

			ServerSocket s = null;
			Socket conn = null;
			DataInputStream dis=null;
			try{
			//1. creating a server socket - 1st parameter is port number and 2nd is the backlog
			s = new ServerSocket(port , 10);
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

			}catch(Exception e)
			{
				System.out.println("Error  "+e.getMessage());
			}
			//Thread.sleep(50);
		/*} catch (InterruptedException e) {
			System.out.println("Thread " +  threadName + " interrupted.");
		}*/
		System.out.println("Thread " +  threadName + " exiting.");
	}

	public void start ()
	{
		System.out.println("Starting " +  threadName );
		if (t == null)
		{
			t = new Thread (this, threadName);
			t.start ();
		}
	}

}


public class TCPServer {

	public static void main(String[] args) throws Exception {
		ThreadServer r=new ThreadServer("thread 1",5001);
		r.start();
		ThreadServer r1=new ThreadServer("thread 2",5002);
		r1.start();
	}
}
