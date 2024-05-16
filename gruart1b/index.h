const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Llums Can Gruart</title>
</head>
<body>
<style>

.button1 {
  width: 120px;
  height: 30px;
  margin-bottom: 10px;
  font-size: 16px;
}

.button2 {
  width: 80px;
  height: 40px;
  margin-bottom: 10px;
  font-size: 16px;
}

.button2.active {
  background-color: #3F3F7F;
}



.button3 {
  width: 74px;
  height: 40px;
  margin-bottom: 10px;
  font-size: 14px;
}

.button3.active {
  background-color: #3F3F7F;
}

.long-slider {
  width: 270px;
  position: absolute;
}

.long-slider1 {
  width: 270px;
  position: absolute;
  transform: translate(1px, -20px);
}

.slider-container {
  position: relative;
  display: inline-block;
}

.slider-value {
  position: absolute;
  top: 0;
  right: -350px;
  margin-to: 5px;
  font-size: 20px;
}

.slider-value1 {
  position: absolute;
  top: 15px;
  right: -315px;
  margin-to: 5px;
  font-size: 20px;
}

.outer-window {
  width: 350px;
  height: 590px;
  padding: 20px;
  border: 2px solid #ccc;
  border-radius: 10px;
  background-color: #297999;
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.inner-window {
  width: 345px; 
  height: 280px;
  padding: 10px;
  border: 2px solid #ccc;
  border-radius: 10px;
  background-color: lightblue;
  position: absolute;
  top: 165px;
  left: 10px;
}

.inner-window2 {
  width: 338px;
  height: 38px;
  padding: 11px;
  border: 2px solid #ccc;
  border-radius: 10px;
  background-color: #306040;
  position: absolute;
  top: 85px;
  left: 15px;
}

.inner-window3 {
  width: 338px;
  height: 38px;
  padding: 11px;
  border: 2px solid #ccc;
  border-radius: 10px;
  background-color: #FFFFFF;
  position: absolute;
  top: 550px;
  left: 14px;
}

.inner-window3 img {
  position: absolute;
  transform: translate(40px, 0px);
}

.inner-window4 {
  width: 312px; 
  height: 35px;
  padding: 11px;
  border: 2px solid #ccc;
  border-radius: 10px;
  background-color: #207070;
  position: absolute;
  top: 480px;
  left: 25px;
}

.outer-window h2 {
  text-align: center;
  margin-top: 0;
}

.custom-title {
  font-size: 20px;
  font-weight: bold;
  transform: translate(0px, -10px);
}

.custom-title1 {
  font-size: 20px;
  font-weight: bold;
  transform: translate(0px, 10px);
}

.circle {
  width: 30px;
  height: 30px;
  border-radius: 50%;
  margin: 2px;
  transform: translate(275px, 10px); 
}

.red {
  background-color: red;
}

.green {
  background-color: green;
}

.blue {
  background-color: blue;
}

</style>

<div class="outer-window">
  <h2 style="color:white;"> IL·LUMINACIÓ CAN GRUART</h2>

  <div class="inner-window">
    <div class="custom-title">Intensitat</div>
      <div class="slider-container">
        <input type="range" id="slider1" min="0" max="255" value="50" class="long-slider" oninput="updateSliderValue(1, this.value)"><br>
        <span id="value1" class="slider-value">50</span>
      </div>
      <br><br>
    <div class="custom-title1">Vermell</div>
      <div class="slider-container">
        <div class="circle red"></div>
        <input type="range" id="slider2" min="0" max="255" value="50" class="long-slider1" oninput="updateSliderValue(2, this.value)"><br>
        <span id="value2" class="slider-value1">50</span>
      </div>
      <br>

    <div class="custom-title1">Verd</div>
      <div class="slider-container">
      <div class="circle green"></div>
        <input type="range" id="slider3" min="0" max="255" value="50" class="long-slider1" oninput="updateSliderValue(3, this.value)"><br>
        <span id="value3" class="slider-value1">50</span>
      </div>
      <br>

    <div class="custom-title1">Blau</div>
      <div class="slider-container">
      <div class="circle blue"></div>
        <input type="range" id="slider4" min="0" max="255" value="50" class="long-slider1" oninput="updateSliderValue(4, this.value)"><br>
        <span id="value4" class="slider-value1">50</span>
      </div>
      <br>
  </div>
  <div class="inner-window2">
    <button onclick="sendData('RGB')" type="button" class="button2" id="boto1">RGB</button>
    <button onclick="sendData('SENY')" type="button" class="button2" id="boto2">SENY</button>
    <button onclick="sendData('ARC')" type="button" class="button2" id="boto3">ARC</button>
    <button onclick="sendData('MOBIL')" type="button" class="button2" id="boto4">MOBIL</button>
  </div>
  <div class="inner-window4">
    <button onclick="sendData('ON')" type="button" class="button3" id="boto9">ON</button>
    <button onclick="sendData('OFF')" type="button" class="button3" id="boto10">OFF</button>
    <button onclick="sendData('RL1_ON')" type="button" class="button3" id="boto11">RL1 ON</button>
    <button onclick="sendData('RL1_OFF')" type="button" class="button3" id="boto12">RL1 OFF</button>
  </div>

  <div class="inner-window3">
    <img src="data:image/png;base64,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" />
    </div>
</div>

<script>
function sendData(frase) {
    fetch("/button?mensaje=" + frase);
}

function updateSliderValue(sliderNum, value) {

    var spanElement = document.getElementById("value" + sliderNum);
    if (spanElement) {

        spanElement.innerText = value;
    }

    fetch("/slider?slider" + sliderNum + "=" + value)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.text();
        })
        .then(data => {
            console.log(data);
        })
        .catch(error => {
            console.error('There was a problem with the fetch operation:', error);
        });
}

window.onload = function(){
    document.getElementById("slider1").value = 50;
    document.getElementById("value1").value = 50;
    document.getElementById("slider2").value = 50;
    document.getElementById("value2").value = 50;
    document.getElementById("slider3").value = 50;
    document.getElementById("value3").value = 50;
    document.getElementById("slider4").value = 50;
    document.getElementById("value4").value = 50;

};


function actualizarMensaje(mensaje) {
    document.getElementById("mensaje").innerText = mensaje;
}
</script>

</body>
</html>
)rawliteral";
