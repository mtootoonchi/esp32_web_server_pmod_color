const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<head>
  <title>Pmod COLOR Website</title>
</head>

<style>
  body{
    margin: 0px;
    background-color: #131313;
  }
  .titleHeader{
    display: inline-block;
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .mainHeaderH10{
    display: inline-block;
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .btn{
    background-color: #444444;
    border: none;
    color: white;
    padding: 10px 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 16px 8px;
    cursor: pointer;
  }
  .mainSection0{
    display: inline-block;
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .mainSectionH10{
    margin-top: 0px;
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .mainSectionH11{
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .mainSectionH12{
    color: aliceblue;
    font-family: "Times New Roman", Times, serif;
  }
  .bottomFooter{
    border-style: solid;
    border-color: whitesmoke;
    height: 25vh;
    width: 25vw;
    background-color: #FFFFFF;
  }
</style>

<body onload="process()">
  <header class="titleHeader">
    <h1 class="mainHeaderH10">Pmod COLOR Website</h1>
    <button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button>
  </header>
  <section>
    <h1 class="mainSectionH10" id="mainSectionH10ID">Red: 0xFF</h1>
    <h1 class="mainSectionH11" id="mainSectionH11ID">Green: 0xFF</h1>
    <h1 class="mainSectionH12" id="mainSectionH12ID">Blue: 0xFF</h1>
  </section>
  <footer class="bottomFooter" id="bottomFooterID">

  </footer>
</body>
<script type = "text/javascript">
  // global variable visible to all java functions
  var xmlHttp=createXmlHttpObject();

  // function to create XML object
  function createXmlHttpObject() {
    if(window.XMLHttpRequest){
      xmlHttp=new XMLHttpRequest();
    }
    else{
      xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlHttp;
  }

  // function to handle button press from HTML code above
  // and send a processing string back to server
  // this processing string is use in the .on method
  function ButtonPress0() {
    var xhttp = new XMLHttpRequest(); 
    xhttp.open("PUT", "BUTTON_0", false);
    xhttp.send();
  }

  // function to handle the response from the ESP
  function response() {
    var redValue;
    var greenValue;
    var blueValue;

    // get the xml stream
    xmlResponse=xmlHttp.responseXML;

    redValue = xmlResponse.getElementsByTagName("B0")[0].firstChild.nodeValue;
    greenValue = xmlResponse.getElementsByTagName("B1")[0].firstChild.nodeValue;
    blueValue = xmlResponse.getElementsByTagName("B2")[0].firstChild.nodeValue;

    document.getElementById("mainSectionH10ID").innerHTML = "Red: 0x" + convert(redValue)
    document.getElementById("mainSectionH11ID").innerHTML = "Green: 0x" + convert(greenValue)
    document.getElementById("mainSectionH12ID").innerHTML = "Blue: 0x" + convert(blueValue)

    document.getElementById("bottomFooterID").setAttribute("style", "background-color: #" + convert(redValue) + convert(greenValue) + convert(blueValue))
  }

  // general processing code for the web page to ask for an XML steam
  // this is actually why you need to keep sending data to the page to 
  // force this call with stuff like this
  // server.on("/xml", SendXML);
  // otherwise the page will not request XML from the ESP, and updates will not happen
  function process() {
   
    if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
      xmlHttp.open("PUT","xml",true);
      xmlHttp.onreadystatechange=response;
      xmlHttp.send(null);
    }       
    // you may have to play with this value, big pages need more porcessing time, and hence
    // a longer timeout
    setTimeout("process()",100);
  }

  function convert(integer) {
    var str = Number(integer).toString(16);
    return str.length == 1 ? "0" + str : str;
  }
</script>
</html>
)=====";