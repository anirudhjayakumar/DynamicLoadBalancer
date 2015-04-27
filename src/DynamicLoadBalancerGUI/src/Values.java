import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;
import org.apache.thrift.transport.TTransportException;


public class Values {

	String ip;
	int port;
	double cpuUtilization;
	int jobsPending;
	int jobsFinished;
	double networkBandwidth;
	double throttleValue;
	DynLBServer.Client dyn;
	
	// client object
	public Values()
	{
		ip="000.0.0.000";
		cpuUtilization=0.0;
		jobsPending=0;
		jobsFinished=0;
		networkBandwidth=0;
		throttleValue=0.0;
		
	}
	public Values(String ip,int port) throws TTransportException
	{
		try {
		      TTransport transport;
		     
		      transport = new TSocket(ip, port);
		      transport.open();

		      TProtocol protocol = new  TBinaryProtocol(transport);
		      dyn = new DynLBServer.Client(protocol);

		      //perform(client);

		      //transport.close();
		    } catch (TException x) {
		      x.printStackTrace();
		    } 
		  

	}
	// method to 
	public String getIp() {
		return ip;
	}
	public void setIp(String ip) {
		this.ip = ip;
	}
	public int getPort() {
		return port;
	}
	public void setPort(int port) {
		this.port = port;
	}
	public double getCpuUtilization() {
		return cpuUtilization;
	}
	public void setCpuUtilization(double cpuUtilization) {
		this.cpuUtilization = cpuUtilization;
	}
	public int getJobsPending() {
		return jobsPending;
	}
	public void setJobsPending(int jobsPending) {
		this.jobsPending = jobsPending;
	}
	public int getJobsFinished() {
		return jobsFinished;
	}
	public void setJobsFinished(int jobsFinished) {
		this.jobsFinished = jobsFinished;
	}
	public double getNetworkBandwidth() {
		return networkBandwidth;
	}
	public void setNetworkBandwidth(double networkBandwidth) {
		this.networkBandwidth = networkBandwidth;
	}
	public double getThrottleValue() {
		return throttleValue;
	}
	public void setThrottleValue(double throttleValue) {
		this.throttleValue = throttleValue;
	}
}
