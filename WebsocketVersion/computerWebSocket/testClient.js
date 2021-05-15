//Used purely to test the server file.

const ws = require("ws"); //required to create websocket client.

//Initialises client
client = new ws("ws://localhost:4200");



//function used to request data periodically
function requestData(){
  client.send("Gib.");
}

//as soon as it connects, it loops, requesting the price every 2 seconds.
client.on('open', function open() {
  requestData();
  setInterval(requestData, 2000);
});

//If the server says that the testclient sent an invalid request (somehow), 
//it causes an error and ends the program.
client.on("message", function receive(msg){
  if(msg=="Invalid request."){
    console.error();
    exit();
  }
  console.log(msg);
});

