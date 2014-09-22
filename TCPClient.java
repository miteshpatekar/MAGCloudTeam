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

public class TCPClient {
	public static int BYTE=1;
	public static int KILOBYTE=1024;
	public static int SIXTYFOURKB=64*1024;

	public static String host = "127.0.0.1";
	public static DataOutputStream dos_out = null;
	public static DataInputStream dis = null;
	public static InputStream is=null;
	public static OutputStream os=null;

	public static void byteTransfer(int blkSize)
	{
		Socket sock = new Socket();
		try
		{
			sock.connect(new InetSocketAddress(host , 5001));
			System.out.println("Connected");


			//Host not found

			os = sock.getOutputStream();
			is = sock.getInputStream();
			long startTime = System.nanoTime();
			String toSend="m";
			System.out.println("Starttime : "+startTime);
			for(int i=0;i<blkSize;i++)
			{
				os.write(toSend.getBytes());
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
			double latency=(endTime-startTime)/1000000;
			System.out.println("Latency :"+latency+" ms");
			//double throughput=(KILOBYTE*1024)/latency
			//System.out.println("Throughput :"+)
		}
		catch (Exception e) 
		{
			System.err.println("Error"+e.getMessage());
			System.exit(1);
		}
	}

	public static void main(String[] args) throws Exception {
		byteTransfer(BYTE);
	}
}
