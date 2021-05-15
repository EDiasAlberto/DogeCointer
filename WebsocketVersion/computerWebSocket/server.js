const ws = require("ws");
const http = require("https");

const server = new ws.Server({
  port:4200
});

const httpOptions = {
  host: 'api.binance.com',
  path: "/api/v3/ticker/price?symbol=DOGEGBP",
};

var dogePrice = "";

let sockets = [];
console.log("Server is running");

function handleData(httpResponse) {
  httpResponse.on("data", function(chunk){
    var chunk = JSON.parse(chunk);
    dogePrice = chunk.price;
    
  });


}


server.on('connection', function(socket) {
  sockets.push(socket);
  console.log("Client has connected.");

  socket.on('message', function(msg) {
    if(msg=="Gib."){
      console.log(msg);
      http.get(httpOptions, handleData).end();

      socket.send(dogePrice);
    }
    else{
      console.log("Invalid request.");
      socket.send("Invalid request.");
    }
  });

  socket.on('close', function() {
    sockets = sockets.filter(s => s !== socket);
    console.log("Client has disconnected.");
  });
});