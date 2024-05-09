const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>TAV ESP32 LED GRUART</title>
<style>
.slider {
    width: 30%;
    margin: 10px;
}
.value {
    margin-left: 10px;
}
</style>
</head>
<body>
<h1>TAV ESP32 LED GRUART</h1>
<div id="mensaje"></div>
<input type="range" id="slider1" class="slider" min="0" max="255" value="50" oninput="updateSliderValue(1, this.value)">
<span id="value1" class="value">50</span><br>
<input type="range" id="slider2" class="slider" min="0" max="255" value="50" oninput="updateSliderValue(2, this.value)">
<span id="value2" class="value">50</span><br>
<input type="range" id="slider3" class="slider" min="0" max="255" value="50" oninput="updateSliderValue(3, this.value)">
<span id="value3" class="value">50</span><br>
<input type="range" id="slider4" class="slider" min="0" max="255" value="50" oninput="updateSliderValue(4, this.value)">
<span id="value4" class="value">50</span><br>
<button type="button" onclick="enviarFrase('ON')">ON</button><br>
<button type="button" onclick="enviarFrase('OFF')">OFF</button><br>
<button type="button" onclick="enviarFrase('LLUM_1')">LLUM 1</button><br>
<button type="button" onclick="enviarFrase('LLUM_2')">LLUM 2</button><br>
<button type="button" onclick="enviarFrase('LLUM_3')">LLUM 3</button><br>
<button type="button" onclick="enviarFrase('LLUM_4')">LLUM 4</button><br>
<button type="button" onclick="resetear()">RESET</button>
<script>

function updateSliderValue(sliderNum, value) {
    document.getElementById("value" + sliderNum).innerText = value;
    fetch("/slider?slider" + sliderNum + "=" + value);
}

function enviarFrase(frase) {
    fetch("/button?mensaje=" + frase);
}

function actualizarMensaje(mensaje) {
    document.getElementById("mensaje").innerText = mensaje;
}

function resetear() {
    document.getElementById("slider1").value = 50;
    document.getElementById("slider2").value = 50;
    document.getElementById("slider3").value = 50;
    document.getElementById("slider4").value = 50;
    document.getElementById("texto").value = "";
}


function obtenerEstadoSliders() {
  fetch("/slidersstatus")
  .then(response => response.text())
  .then(data => {
    console.log("Estado de los sliders:", data);
    // Haz algo con los estados de los sliders, como actualizar la interfaz de usuario
    var estados = data.split(",");
    var slider1 = estados[0];
    var slider2 = estados[1];
    var slider3 = estados[2];
    var slider4 = estados[3];
    // Actualiza la interfaz de usuario con los valores de los sliders
    document.getElementById("value1").innerText = slider1;
    document.getElementById("value2").innerText = slider2;
    document.getElementById("value3").innerText = slider3;
    document.getElementById("value4").innerText = slider4;
  });
}
// Llama a esta función para obtener el estado de los sliders
obtenerEstadoSliders();
</script>
</body>
</html>
)rawliteral";
