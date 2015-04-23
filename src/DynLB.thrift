namespace cpp Comm

/*
 C like comments are supported
*/
// This is also a valid comment

service DynLBServer
{
	oneway void SendJobsToRemote(1:i32 size, 2:list<binary> vJobs);
	oneway void RequestJobsFromRemote(1:i32 nJobs);
	oneway void SendStateToRemote(1:binary stateBlob);
	oneway void RequestStateFromRemote();
	oneway void SendCompletedJobsToRemote(1:i32 size, 2:list<binary> vJobs);
	oneway void RequestCompletedJobsFromRemote();
	// we will need synchronous calls during GUI impl to be called 
	// from java UI since server has no proxy to the UI client.
}
