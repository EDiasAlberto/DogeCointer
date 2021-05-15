const ws = require("ws");


client = new ws("ws://localhost:4200");




function requestData(){
  client.send("Gib.");
}

client.on('open', function open() {
  requestData();
  setInterval(requestData, 2000);
});

client.on("message", function receive(msg){
  if(msg=="Invalid request."){
    console.error();
    exit();
  }
  console.log(msg);
});

