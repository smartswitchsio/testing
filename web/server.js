var ws = null;
function sendBlob(str){
  var buf = new Uint8Array(str.length);
  for (var i = 0; i < str.length; ++i) buf[i] = str.charCodeAt(i);
  ws.send(buf);
}
function startSocket(){
  ws = new WebSocket('ws://'+document.location.host+'/ws',['arduino']);
  ws.binaryType = "arraybuffer";
  ws.onopen = function(e){
   
    var data = "{\"id\":\"connected\"}";
          sendserver(data);
  };
  ws.onclose = function(e){
    
  };
  ws.onerror = function(e){
    console.log("ws error", e);
    
  };
  ws.onmessage = function(e){
    var msg = "";
    if(e.data instanceof ArrayBuffer){
      msg = "BIN:";
      var bytes = new Uint8Array(e.data);
      for (var i = 0; i < bytes.length; i++) {
        msg += String.fromCharCode(bytes[i]);
      }
    } else {
     
      msg = e.data;
    }
   
    splitdata(msg);
  };
  
}
/*function startEvents(){
  var es = new EventSource('/events');
  es.onopen = function(e) {
  
  };
  es.onerror = function(e) {
    if (e.target.readyState != EventSource.OPEN) {

    }
  };
  es.onmessage = function(e) {

    console.log("Event: " + e.data);
  };
  es.addEventListener('ota', function(e) {
    
  }, false);
}*/
function onBodyLoad(){
  startSocket();
  dislabel();
  //startEvents();
}
/////////////////////////Send all in one/////////////////////////////////
function sendserver(data){
    console.log(data);
    
    ws.send(data);
    }
/////////////////////////////////////////////
$(document).ready(function(){
///////////////Switch send data to server///////////////////
    $("#switch0").click(function(){
        if (this.checked) {
       sendserver("{\"id\":\"swsts\",\"sw\":\"on0\"}");
       $("#led0").removeClass();
         $('#led0').addClass('led-green');

       } else if(!this.checked) {
        sendserver("{\"id\":\"swsts\",\"sw\":\"off0\"}");
         $("#led0").removeClass();
         $('#led0').addClass('led-gray');
       } 
         });

    $("#switch1").click(function(){
       if (this.checked) {
       sendserver("{\"id\":\"swsts\",\"sw\":\"on1\"}");
       $("#led1").removeClass();
         $('#led1').addClass('led-green');

       } else if(!this.checked) {
        sendserver("{\"id\":\"swsts\",\"sw\":\"off1\"}");
      $("#led1").removeClass();
         $('#led1').addClass('led-gray');
       }
   });

    $("#switch2").click(function(){
       if (this.checked) {
       sendserver("{\"id\":\"swsts\",\"sw\":\"on2\"}");
       $("#led2").removeClass();
         $('#led2').addClass('led-green');

       } else if(!this.checked) {
       sendserver("{\"id\":\"swsts\",\"sw\":\"off2\"}");
$("#led2").removeClass();
         $('#led2').addClass('led-gray');
       }
   });

     });
//////////////////All input///////////////////
 //////////////////Split data//////////////
 function splitdata(data) {
	var obj = JSON.parse(data);
  //console.log(obj);
  switch (obj.id) {

    case "clk":
    livetime(obj);
	  break;
		  
    case "status":
    status(obj);
    break;

    default:
    console.log(obj);
    break;

}
}
////////////////live time/////////////
function livetime(obj){
  //document.getElementById("livetime").innerHTML = epoch(time);
   $("#livetime").html(epoch(obj));
   }
  
  function epoch(obj){
  var myDate = new Date( obj.tm *1000);
  var date = myDate.toLocaleString('en-US',{hour12:false}).split(" ");
   
  var time = date[1];
  var mdy = date[0];
  //var tmp = obj.tp;
  
  // We then parse  the mdy into parts
  mdy = mdy.split('/');
  var month = parseInt(mdy[0]);
  var day = parseInt(mdy[1]);
  if(month.toString().length == 1) {month = "0" + month;}
  if(day.toString().length == 1) {day = "0" + day;}
  var year = parseInt(mdy[2]);
  
  var formattedDate = 'Date' + ' ' + day + '-' + month + '-' + year + ' ' + 'Time' + ' ' + time;
  
  return formattedDate;
  } 