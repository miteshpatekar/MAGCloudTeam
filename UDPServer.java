import java.io.*;
import java.net.*;

class UDPServer 
{
	public static void main(String args[]) throws Exception
	{

		DatagramSocket serverSocket = 
				new DatagramSocket(9876);

		byte[] receiveData = new byte[1024];
		byte[] sendData;

		while(true)
		{
			System.out.println("Listening to client");
			DatagramPacket receivePacket =
					new DatagramPacket(receiveData, receiveData.length);

			serverSocket.receive(receivePacket);

			String sentence = new String(receivePacket.getData(),
					0, receivePacket.getLength());
			System.out.println("data "+receivePacket.getLength());
			System.out.println("data rec "+sentence);;
			InetAddress IPAddress = receivePacket.getAddress();

			int port = receivePacket.getPort();

			// String capitalizedSentence = sentence.toUpperCase();
			String ack="y";

			sendData = ack.getBytes();

			DatagramPacket sendPacket =
					new DatagramPacket(sendData, sendData.length,
							IPAddress, port);

			serverSocket.send(sendPacket);
		}
	}
}
