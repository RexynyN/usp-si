﻿using System.Net;
using System.Net.Sockets;
using System.Text.Json;

namespace XadrezServer
{
    class MyTcpListener
    {

        public static void Main(String[] args)
        {
            TcpListener? server = null;

            try
            {
                // Set the TcpListener on port 13000.
                Int32 port = 13000;
                IPAddress localAddr = IPAddress.Parse("127.0.0.1");

                // TcpListener server = new TcpListener(port);
                server = new TcpListener(localAddr, port);

                // Start listening for client requests.
                server.Start();

                // Buffer for reading data
                Byte[] bytes = new Byte[256];
                String? data = null;
                String? response = null;

                System.Console.WriteLine("Servidor Rodando!");
                // Enter the listening loop.
                while (true)
                {
                    // Console.Write("Waiting for a connection... ");

                    // Perform a blocking call to accept requests.
                    // You could also use server.AcceptSocket() here.
                    TcpClient client = server.AcceptTcpClient();
                    // Console.WriteLine("Connected!"); 
                    data = null;

                    // Get a stream object for reading and writing
                    NetworkStream stream = client.GetStream();
                    int i;

                    // Loop to receive all the data sent by the client.
                    while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        // Translate data bytes to a ASCII string.
                        data = System.Text.Encoding.UTF8.GetString(bytes, 0, i);
                        // Console.WriteLine("Received: {0}", data);

                        string[] datas = data.Split("$");

                        // Representa a ação a ser tomada na chamada (algo como uma rota em uma API)
                        string action = datas[0].Trim().Replace("\"", "");

                        // Conteúdo do pacote
                        string content = datas[1].Trim();

                        // Processa o conteúdo do pedido
                        response = Router.HandleAction(action, content);

                        // Pega os bytes da resposta
                        byte[] msg = System.Text.Encoding.UTF8.GetBytes(response);

                        // Send back a response.
                        stream.Write(msg, 0, msg.Length);
                        // Console.WriteLine("Sent: {0}", response);

                    }

                    // Shutdown and end connection
                    client.Close();
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            }
            catch(Exception e)
            {
                Console.WriteLine("An exception occured while serving a request: {0}", e);
            }

            server?.Stop();
            Console.WriteLine("\nHit enter to continue...");
            Console.Read();
        }

    }
}
    