package com.java.socket;

//java socket client example
import java.io.*;
import java.util.Date;
import java.net.*;
import java.lang.*;

public class Client
{
  public static void main(String[] args) throws IOException 
  {
    Socket s = new Socket();
  	String host = "127.0.0.1";
  	PrintWriter c_out = null;
  	BufferedReader c_in = null;
  	DataOutputStream dos_out = null;
    DataInputStream dos_in = null;

  	
      try
      {
      s.connect(new InetSocketAddress(host , 5001));
      System.out.println("Connected");
           
      //writer for socket
          c_out = new PrintWriter(s.getOutputStream(), true);
         
	//reader for socket
          c_in = new BufferedReader(new InputStreamReader(s.getInputStream()));
      }
       
      //Host not found
      catch (UnknownHostException e) 
      {
          System.err.println("Don't know about host : " + host);
          System.exit(1);
      }

    //  long lDateTime = new Date().getTime();
      
     // System.out.println("Date() - Time in milliseconds: " + lDateTime);
       
      long a = System.nanoTime();
      System.out.println(a);
    //Send message to server
      String message = "Hello!!! How are you??? Welcome to my world...!!!";
    
      dos_out = new DataOutputStream(new BufferedOutputStream(s.getOutputStream()));
      dos_in = new DataInputStream(new BufferedInputStream(s.getInputStream()));
    
      System.out.println(message.getBytes("utf8").length);
      c_out.println( message );
     
      byte[] sendMessage = new byte[(int)message.length()];
      dos_out.write(sendMessage);
      
      System.out.println("length of the message:"+sendMessage.length);
  
      System.out.println(message);
      long b = System.nanoTime();
      System.out.println(b);
  
      System.out.println("Latency:"+(b-a)/sendMessage.length);
      
     
  
  //Get response from server
  String response;
  while ((response = c_in.readLine()) != null) 
  {
      System.out.println( response );
  }



try
        {
          s.close();
        }
       
      catch(IOException ioException)
        {
          System.err.println("Unable to close. IOexception");
        }
	}








  //FileInputStream fis = new FileInputStream(f);
  //BufferedInputStream bis = new BufferedInputStream(fis);
  //BufferedOutputStream out = new BufferedOutputStream(s.getOutputStream());

  




/*

  File f = new File("C:\\Users\\Aditya1991\\Pictures\\butterfly.jpg");
  // Get the size of the file
  long length = f.length();
  if (length > Integer.MAX_VALUE) {
      System.out.println("File is too large.");
  }
*/


/*
int count;
	long start = System.nanoTime();


	while ((count = bis.read(bytes)) > 0) {
      	out.write(bytes, 0, count);
  	}


	long end = System.nanoTime();
	long microseconds = (end - start) / 1000;
  
	System.out.println(microseconds);


*/



/* String msg = "Hello World! Welcome..!!"; 


	byte[] bytes = new byte[msg.length()];


  	BufferedOutputStream out = new BufferedOutputStream(s.getOutputStream());
  
	  try {
      	out.write(bytes, 0, msg.length()); 
		System.out.println("Data bytes sent:"+bytes);
      	
  	      } catch (IOException e) {
      e.printStackTrace();
	    }
	*/


}
