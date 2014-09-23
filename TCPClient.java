import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;

class ThreadClient implements Runnable {
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


	ThreadClient( String name, int size,int portno){
		threadName = name;
		blkSize = size;
		port=portno;
		System.out.println("Creating " +  threadName );
	}
	public void run() {
		System.out.println("Running " +  threadName );
		//try {
		Socket sock = new Socket();
		try
		{
			sock.connect(new InetSocketAddress(host , port));
			System.out.println("Connected");
			//Host not found

			os = sock.getOutputStream();
			is = sock.getInputStream();
			long startTime = System.nanoTime();
			String toSend="m";
			System.out.println("Starttime : "+startTime);
			for(int j=0;j<100;j++)
			{
				for(int i=0;i<blkSize;i++)
				{
					os.write(toSend.getBytes());
				}
			}
			while(true)
			{
				// create data input stream
				dis = new DataInputStream(is);
				try {
					if( dis.available() >0)
					{
						// read one single byte
						byte b = dis.readByte();
						// print the byte
						System.out.println((char)b+" is the returned byte");
						break;
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			long endTime = System.nanoTime();
			System.out.println("Endtime : "+endTime );
			double latency=(endTime-startTime)/2*1000000;
			System.out.println("Latency :"+latency+" ms");
			double throughput=(BYTE*1000*100)/(latency*1024*1024);
			System.out.println("Throughput :"+throughput);
		}
		catch (Exception e) 
		{
			System.err.println("Error"+e.getMessage());
			System.exit(1);
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

public class TCPClient {
	public static void main(String[] args) throws Exception {
		//byteTransfer(BYTE);
		
		ThreadClient r=new ThreadClient("thread 1",1,5001);
		r.start();
		ThreadClient r1=new ThreadClient("thread 2",1,5002);
		r1.start();
	}
}
