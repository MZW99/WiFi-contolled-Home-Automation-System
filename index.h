const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <title>A Home Automation Temperature and Moisture Control System</title>
  <style type="text/css">
    button{
      width:100px;
      height: 50px;
      background-color:palegoldenrod;
    }
  </style>
  </head> 

<summary> <b> A Home Automation Temperature and Moisture Control System<br>
</summary>

<hr color = pink>
  <details class="menu" open>
  <summary><b>Function 1: Contorl the LEDs<br>
  </b>
  </summary>
  <p>
  <button type="button" onClick='sendData(1)'>POWER ON </button><br>
  <p>
  <button type="button" onClick='sendData(0)'>POWER OFF </button>
  <p>
 <div>
  POWER Status: <span id="LEDState">NA</span><br>
 </div>
   </details> 
   
<hr color = pink>
    <details class="menu" open>
  <summary>
    <b>Function 2: Real time temperature and moisture<br>
  </b>
  </summary>
  <div>
  <p style="color:blue;">Temperature: <span id = "TEMP">0</span> &#8451<p></p>
  <p style="color:blue;">Moisture: <span id = "HUM">0</span> &#37<p></p>
  </div>
   </details>

<hr color = pink>
  <details class="menu" open>
  <summary>
  <b>Function 3: Change modes
  </b>
  </summary>
  <p>   
      <button type="button" onclick='setflags(1)'>COOL</button>
      <button type="button" onclick='setflags(2)'>HEAT</button>
   <div>
   MODE: <span id="MODEState">NA</span><br>
  </div>
  </details>

<hr color = pink> 
  <details class="menu" open>
  <summary>
  <b>Function 4: Temperature control
  </b>
  </summary>
  <p>   
      <button type="button" onclick='setTemp(1)'>INCREASE</button>
      <button type="button" onclick='setTemp(2)'>DECREASE</button>
   <div>
   Temperature: <span id="SetTemp">NA</span><br>
  </div>
  </details>

<hr color = pink> 
 
<script>
function sendData(led) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    document.getElementById("LEDState").innerHTML =
    this.responseText;
    }
    };
    xhttp.open("GET", "setLED?LEDstate="+led, true);
    xhttp.send();
}

function setflags(flags){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    document.getElementById("MODEState").innerHTML =
    this.responseText;
    }
    };
    xhttp.open("GET", "setMODE?MODEstate="+flags, true);
    xhttp.send();
}

setInterval(function() {
  getTemp();
  getHum();
}, 2000); 

function getTemp() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("TEMP").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readTEMP", true);
  xhttp.send();
}

function getHum() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("HUM").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readHUM", true);
  xhttp.send();
}

function setTemp(t){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    document.getElementById("SetTemp").innerHTML =
    this.responseText;
    }
    };
    xhttp.open("GET", "settemp?TEMPstate="+t, true);
    xhttp.send();
}
</script>
  </body>
</html>
)=====";
