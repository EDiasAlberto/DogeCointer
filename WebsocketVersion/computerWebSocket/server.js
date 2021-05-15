//Two libraries needed to start the server and request the dogecoin price
const ws = require("ws");
const http = require("https");

//Starts the server object
const server = new ws.Server({
  port:4200
});

//Sets the options for the http request
const httpOptions = {
  host: 'api.binance.com',
  path: "/api/v3/ticker/price?symbol=DOGEGBP",
};

//sets the variable so it can be easily printed later
var dogePrice = "";

//sets the empty list in case more than one socket is connected.
let sockets = [];
console.log("Server is running");

function handleData(httpResponse) {
  httpResponse.on("data", function(chunk){
    var chunk = JSON.parse(chunk);
    dogePrice = chunk.price;
    
  });


}

//Handles the connection of new sockets
server.on('connection', function(socket) {
  sockets.push(socket);
  console.log("Client has connected.");

  //when the client sends any message, if it is "Gib.", then it responds with the price of dogecoin.
  socket.on('message', function(msg) {
    if(msg=="Gib."){
      console.log(msg);
      http.get(httpOptions, handleData).end();

      socket.send(dogePrice);
    }
    else{
      //Informs both client and server of invalid message.
      console.log("Invalid request."); 
      socket.send("Invalid request.");
    }
  });

  socket.on('close', function() {
    sockets = sockets.filter(s => s !== socket);
    console.log("Client has disconnected.");
  });
});