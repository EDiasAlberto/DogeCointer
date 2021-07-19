//Used purely to test the server file.
const prompt = require('prompt-sync')();
const { exit } = require("process");
const ws = require("ws"); //required to create websocket client.

//Initialises client
client = new ws("ws://localhost:4200");


//function used to request data periodically
function requestData(currency){
  client.send(currency);
}

//as soon as it connects, it loops, requesting the price every 2 seconds.
client.on('open', function open() {
  let currencyPair = prompt("Please enter a currency pair: ");
  requestData(currencyPair);
  setInterval(requestData, 2000, currencyPair);
});

//If the server says that the testclient sent an invalid request (somehow), 
//it causes an error and ends the program.
client.on("message", function receive(msg){
  if(msg=="Invalid request."){
    console.error();

  }
  console.log(msg);
});

