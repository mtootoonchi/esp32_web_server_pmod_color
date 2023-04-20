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

<body>
  <header class="titleHeader" id="titleHeaderID">
    <h1 class="mainHeaderH10">Pmod COLOR Website</h1>
    <button type="button" class = "btn" id = "btn0" onclick="ButtonPress0()">Toggle</button>
  </header>
  <section>
    <h1 class="mainSectionH10">Red: 0xFF</h1>
    <h1 class="mainSectionH11">Green: 0xFF</h1>
    <h1 class="mainSectionH12">Blue: 0xFF</h1>
  </section>
  <footer class="bottomFooter" id="bottomFooterID">

  </footer>
</body>
<script type = "text/javascript">
  
</script>
</html>
)=====";