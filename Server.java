package com.java.socket;

import java.io.*;
import java.net.*;
 
public class Server
{
    public static void main(String args[])
    {
        ServerSocket s = null;
        Socket conn = null;
        PrintStream s_out = null;
        BufferedReader s_in = null;


        InputStream is = null;
    	BufferedOutputStream bos = null;
    	DataInputStream dis = null;
    	int bufferSize = 0;
         
        try
        {
            //1. creating a server socket - 1st parameter is port number and 2nd is the backlog
            s = new ServerSocket(5001 , 10);
        
            //2. Wait for an incoming connection
            System.out.println("Server socket created. Waiting for connection...");
            
            //get the connection socket
            conn = s.accept();
            
            //print the hostname and port number of the connection
            System.out.println("Connection received from " + conn.getInetAddress().getHostName() + " : " + conn.getPort());
             
            //3. get Input and Output streams

            s_out = new PrintStream(conn.getOutputStream());
            s_out.flush();

            s_in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
             
            s_out.println("Welcome. Server version 1.0");
            s_out.flush();

	    //Get response from client
            

           String c_response;
           dis = new DataInputStream(new BufferedInputStream(conn.getInputStream()));

           
           while ((c_response = s_in.readLine()) != null) 
           {
        	 
        	   //is = conn.getInputStream();
               //bufferSize = conn.getReceiveBufferSize();
        	   
        	   byte b[] = new byte[2048];
        	  // int nosRead = conn.getInputStream().read(b);
        	   dis.read(b);
               System.out.println("Bytes received: " + b);
               System.out.println( c_response +" received from Client!" );
            
           }
           
           
          
	//try {
     	   
    	//    } 
	
	/*catch (IOException ex) {
        	System.out.println("Can't get socket input stream. ");
    	    }
    	    */
	  

        /*byte[] bytes = new byte[bufferSize];

        int count;

       // try {
			while ((count = is.read(bytes)) > 0) {
			    bos.write(bytes, 0, count);
			    System.out.println("Bytes received:"+bytes);
			}*/
		//	}


/*

    byte[] bytes = new byte[bufferSize];

    int count;

    while ((count = is.read(bytes)) > 0) {
        bos.write(bytes, 0, count);
    }
*/

       
            
        }
            catch (IOException e) {
    			// TODO Auto-generated catch block
    			e.printStackTrace();
    		}
        
        finally{
        	try {
				s_in.close();
				s_out.close();
	            s.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            
        }
    }
        
        
           // System.err.println("Unable to close. IOexception");
        
       


/* try {
		is= new InputStream(conn.getInputStream());
		int len = is.readInt();

	        if(len>0) {
   		byte[] msg = new byte[len];
    		is.readFully(msg); // read the message
		System.out.println("Data bytes received: "+msg);
		}
    	} 
	
	catch (IOException ex) {
        System.out.println("Can't get socket input stream. ");
	}

	*/

}
