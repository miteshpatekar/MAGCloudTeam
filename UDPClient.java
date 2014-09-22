import java.io.*;
import java.net.*;

class UDPClient 
{
	public static int BYTE=1;
	public static int KILOBYTE=1024;
	public static int SIXTYFOURKB=64*1024;

	public static void udpTransfer(int blkSize)
	{
		BufferedReader inFromUser =
				new BufferedReader(
						new InputStreamReader(System.in));
		byte[] sendData;
		byte[] receiveData = new byte[10];
		String toSend="m";

		try
		{
			DatagramSocket clientSocket = new DatagramSocket();
			InetAddress IPAddress = InetAddress.getByName("127.0.0.1");
			long startTime=System.nanoTime();
			for(int i=0;i<blkSize;i++)
			{
				sendData = toSend.getBytes();
				DatagramPacket sendPacket =
						new DatagramPacket(sendData, sendData.length,
								IPAddress, 9876);
				clientSocket.send(sendPacket);
			}
			DatagramPacket receivePacket =
					new DatagramPacket(receiveData, receiveData.length);

			clientSocket.receive(receivePacket);

			String modifiedSentence = new String(receivePacket.getData(),
					0, receivePacket.getLength());

			System.out.println("FROM SERVER: " + modifiedSentence);
			long endTime=System.nanoTime();
			double latency=(endTime-startTime)/1000000;
			System.out.println("Latency : "+latency+" ms");
			clientSocket.close();
		}
		catch(Exception e){
			System.out.println("Error "+e.getMessage());

		}finally{
			//BufferedReader clientSocket;
		}
	}

	public static void main(String args[]) throws Exception
	{
		udpTransfer(SIXTYFOURKB);
	}
}
