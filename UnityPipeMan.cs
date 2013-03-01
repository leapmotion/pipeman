using System.Runtime.InteropServices;
using System;
using System.Text;

public class Piper {
	
	[DllImport ("PipeManC")]
	private static extern IntPtr Server_Create( string name, long buffercount, long bufferSize);
	
	[DllImport ("PipeManC")]
	private static extern int Server_Destroy(IntPtr handle);
	
	[DllImport ("PipeManC")]
	private static extern  bool Server_SendData(IntPtr handle, byte [] data, int size);
	
	[DllImport ("PipeManC")]
	private static extern bool Server_Flip(IntPtr handle, int timeout);
	
	[DllImport ("PipeManC")]
	private static extern bool Server_Flip_NoTimeout(IntPtr handle);
	
	
	private IntPtr m_handle;
	
	public Piper(string name, long buffercount, long bufferSize) { 
		m_handle = Server_Create(name, buffercount, bufferSize);
	}
	
	~Piper()
	{
		Server_Destroy(m_handle);
	}
	
	public void Send(byte[] data)
	{
		Server_SendData(m_handle, data, data.Length);	
	}
	
	public bool Flush()
	{
		return Server_Flip_NoTimeout(m_handle);	
	}
};