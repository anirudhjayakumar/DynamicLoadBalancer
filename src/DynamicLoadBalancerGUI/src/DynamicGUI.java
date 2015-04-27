import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.AbstractCellEditor;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

public class DynamicGUI {
	//Values v;
	DynLBServer.Client dyn1;
	DynLBServer.Client dyn2;
	 static JFrame frame = new JFrame("Dynamic Load Balancer");
	 static JPanel layout = new JPanel(new BorderLayout());
	 
	static Font f = new Font("", Font.PLAIN, 20);
	 public static void main(String args[]) {
		 
		 DynamicGUI gui = new DynamicGUI();
		 DynLBServer.Client dyn1;
		 DynLBServer.Client dyn2;
		 Values v1= new Values();
		 Values v2 = new Values();
		   JTable table1 = gui.makeTable(1);
		   table1.setFont(f); 
		   table1.setForeground(Color.BLUE);
		   JTable table2 = gui.makeTable(2);
		   table2.setFont(f); 
		   table2.setForeground(Color.MAGENTA);
		  // JFrame frame = new JFrame("Dynamic Load Balancer");
		   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		   JScrollPane scrollPane1 = new JScrollPane(table1);
		   JScrollPane scrollPane2 = new JScrollPane(table2);
		  // frame.add(scrollPane1, BorderLayout.WEST);
		  // frame.add(scrollPane2, BorderLayout.EAST);
		   layout.add(scrollPane1, BorderLayout.WEST);
		   layout.add(scrollPane2, BorderLayout.EAST);
		   frame.add(layout);
		   frame.validate();
		   frame.pack();
		   frame.setVisible(true);
		   dyn1 = gui.communicateLocal();
		   dyn2 = gui.communicateRemote();
		   int i=0;
		   while(i==0)
		   {
			   System.out.println("Entered while loop");
			   try {
				    Thread.sleep(2000);                 //2000 milliseconds is one second.
				} catch(InterruptedException ex) {
				    Thread.currentThread().interrupt();
				}
		  try{
			    
			     v1.setCpuUtilization(dyn1.GetStateInfo().getCpu_util());
			     v1.setJobsPending(dyn1.GetStateInfo().getNJobsPending());
			     v1.setJobsFinished(dyn1.GetStateInfo().getNJobsCompleted());
			    // v1.setNetworkBandwidth(dyn1.GetStateInfo().getDNetwork());
			     v1.setThrottleValue(dyn1.GetStateInfo().getFThrottling());
			     System.out.println("Throttle Value for local "+dyn1.GetStateInfo().getFThrottling());
			     v1.setIp("172.22.156.65");
			     v1.setPort(9090);
			     
			    } catch (TException x) {
			      x.printStackTrace();
			    } 
		   try {
			     
			      v2.setCpuUtilization(dyn2.GetStateInfo().getCpu_util());
				  v2.setJobsPending(dyn2.GetStateInfo().getNJobsPending());
				  v2.setJobsFinished(dyn2.GetStateInfo().getNJobsCompleted());
				 // v2.setNetworkBandwidth(dyn2.GetStateInfo().getDNetwork());
				  v2.setThrottleValue(dyn2.GetStateInfo().getFThrottling());
				  v2.setIp("172.22.156.5");
				  v2.setPort(9090);
			    } catch (TException x) {
			      x.printStackTrace();
			    } 
		   gui.refresh(table1, table2, v1,v2);
		   }
		  }

	public  JTable makeTable(int i) {
		JTable table;
		Vector<String> rowOne = new Vector<String>();
            if(i==1)
            {
		    rowOne.addElement("Node 1");
		    rowOne.addElement("Local Node");
		    }
            else 
           if(i==2)
           {
        	rowOne.addElement("Node 2");
   		    rowOne.addElement("Remote Node");
           }

		    
		    Vector<String> rowTwo = new Vector<String>();
		    rowTwo.addElement("IP Address");
		    rowTwo.addElement("000.00.000.0");
		    Vector<String> rowThree = new Vector<String>();
		    rowThree.addElement("Port");
		    rowThree.addElement("9090");
		    Vector<String> rowFour = new Vector<String>();
		    rowFour.addElement("CPU Utilization");
		    rowFour.addElement("0");
		    Vector<String> rowFive = new Vector<String>();
		    rowFive.addElement("No. of Jobs Pending");
		    rowFive.addElement("0");
		    Vector<String> rowSix = new Vector<String>();
		    rowSix.addElement("No. of Jobs Completed");
		    rowSix.addElement("0");
		   /* Vector<String> rowSeven = new Vector<String>();
		    rowSeven.addElement("Network Bandwidth");
		    rowSeven.addElement("0");*/
		    Vector<String> rowEight = new Vector<String>();
		    rowEight.addElement("Throttling Value");
		    rowEight.addElement("1.0");
		    JPanel toolbarLayout = new JPanel(new FlowLayout(FlowLayout.LEFT));
		    JLabel throttle1 = new JLabel("Throttle Value for Local Node ");
		    toolbarLayout.add(throttle1);
	    	DefaultComboBoxModel throttle1options = new DefaultComboBoxModel();
	    	throttle1options.addElement("1.0");
	    	throttle1options.addElement("0.75");
	    	throttle1options.addElement("0.5");
	    	throttle1options.addElement("0.25");
	    	throttle1options.addElement("0.1");
	    	
	    	final JComboBox throttlelocal = new JComboBox(throttle1options);    
	    	throttlelocal.setSelectedIndex(0);
	    	throttlelocal.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					JComboBox source = (JComboBox) e.getSource();
					if(dyn1!=null)
					{
						try {
							dyn1.SetThrottling(Double.parseDouble(source.getSelectedItem().toString()));
							System.out.println("Throttling value for local "+dyn1.GetStateInfo().getFThrottling());
						} catch (NumberFormatException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (TException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					}
				}
			});
	    	JScrollPane localScrollPaneD = new JScrollPane(throttlelocal); 
	        toolbarLayout.add(localScrollPaneD);
	        JLabel space = new JLabel("                                                                          ");
	        toolbarLayout.add(space);
			  JLabel throttle2 = new JLabel("Throttle Value for Remote Node ");
			   toolbarLayout.add(throttle2);
		    	DefaultComboBoxModel throttle2options = new DefaultComboBoxModel();
		    	throttle2options.addElement("1.0");
		    	throttle2options.addElement("0.75");
		    	throttle2options.addElement("0.5");
		    	throttle2options.addElement("0.25");
		    	throttle2options.addElement("0.1");
		    	
		    
		    	
		    	final JComboBox throttleremote = new JComboBox(throttle2options);    
		    	throttleremote.setSelectedIndex(0);
		    	throttleremote.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						JComboBox source = (JComboBox) e.getSource();
						if(dyn2 != null){
							try {
								dyn2.SetThrottling(Double.parseDouble(source.getSelectedItem().toString()));
								System.out.println("Throttle Value being set for remote ");
							} catch (NumberFormatException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							} catch (TException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
						 ;
					}
				});
		    	JScrollPane remoteScrollPaneD = new JScrollPane(throttleremote); 
		        toolbarLayout.add(remoteScrollPaneD);
				 
		    	 layout.add(toolbarLayout,BorderLayout.SOUTH);
		    Vector<Vector> rowData = new Vector<Vector>();
		    rowData.addElement(rowOne);
		    rowData.addElement(rowTwo);
		    rowData.addElement(rowThree);
		    rowData.addElement(rowFour);
		    rowData.addElement(rowFive);
		    rowData.addElement(rowSix);
		    //rowData.addElement(rowSeven);
		    rowData.addElement(rowEight);
		    Vector<String> columnNames = new Vector<String>();
		    columnNames.addElement("PARAMETERS");
		    columnNames.addElement("VALUES");
		    table = new JTable(rowData, columnNames);
		    table.setAutoResizeMode(JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS);
		    table.setRowHeight(50);
		return table;
	}
	void refresh(JTable table1, JTable table2,Values v1,Values v2){
	table1.setValueAt(v1.getIp(), 1, 1);
	System.out.println(v1.getIp());
	table1.setValueAt(v1.getPort(), 2, 1);
	table1.setValueAt(v1.getCpuUtilization(), 3, 1);
	table1.setValueAt(v1.getJobsPending(), 4, 1);
	table1.setValueAt(v1.getJobsFinished(),5,1);
	//table1.setValueAt(v1.getNetworkBandwidth(), 6,1);
	table1.setValueAt(v1.getThrottleValue(), 6, 1);
	
	table2.setValueAt(v2.getIp(), 1, 1);
	table2.setValueAt(v2.getPort(), 2, 1);
	table2.setValueAt(v2.getCpuUtilization(), 3, 1);
	table2.setValueAt(v2.getJobsPending(), 4, 1);
	table2.setValueAt(v2.getJobsFinished(),5,1);
	//table2.setValueAt(v2.getNetworkBandwidth(), 6,1);
	table2.setValueAt(v2.getThrottleValue(), 6, 1);
	}
	
	public DynLBServer.Client communicateLocal()
	{
		 try {
		      TTransport transport;
		      transport = new TSocket("172.22.156.65", 9090);
		      transport.open();
		      TProtocol protocol = new  TBinaryProtocol(transport);
		      dyn1 = new DynLBServer.Client(protocol);
		      System.out.println("Connection to local successful. 172.22.156.65");
		 }
		 catch (TException x) {
		      x.printStackTrace();
		    } 
		 return dyn1;
	}
	
	public DynLBServer.Client communicateRemote()
	{
		 try {
		      TTransport transport2;
		      transport2 = new TSocket("172.22.156.5", 9090);
		      transport2.open();
		      TProtocol protocol2 = new  TBinaryProtocol(transport2);
		      dyn2 = new DynLBServer.Client(protocol2);
		      System.out.println("Connection to remote successful. 172.22.156.5");
		 }
		 catch (TException x) {
		      x.printStackTrace();
		    } 
	return dyn2;
	}
}
