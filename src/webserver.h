#ifndef WEBSERVER_H
#define WEBSERVER_H


String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Scroll TEXT server</title>
  <style>
    body {font-family: Arial, sans-serif; background-color: #22d892; color: #333; display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100vh; margin: 0; }
    .container { background: #ffffff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); text-align: center; }
    input[type="text"] { padding: 10px; width: 80%; margin-bottom: 20px; border: 1px solid #ccc; border-radius: 4px; }
    button, input[type="submit"] { padding: 10px 20px; background-color: #28a745; color: #fff; border: none; border-radius: 4px; cursor: pointer; }
    button:hover, input[type="submit"]:hover { background-color: #218838; }
    .info { font-weight: bold; margin-top: 20px; font-size: 0.9em; color: #b82c2c; }
    .radio-group { margin: 20px 0; }
    .radio-group label { margin-right: 10px; }
    input:hover {background-color: rgb(215, 228, 41);}
  </style>
</head>
<body>
  <div class="container">
    <h1>ESP8266 Text Display</h1>
    <form action="/updateText" method="post">
      <input type="text" name="text" placeholder="Enter text" required>
      <button type="submit">Update Text</button>
    </form>
    <form action="/updateDirection" method="post">
      <label><input type="radio" name="direction" value="left" checked> Left</label>
      <label><input type="radio" name="direction" value="right"> Right</label>
      <label><input type="radio" name="direction" value="up"> Up</label>
      <label><input type="radio" name="direction" value="down"> Down</label>
      <button type="submit">Update Direction</button>
    </form>
    <div class="info">
        <p>Author: <span id="author"></span></p>
        <p>GitHub: <a id="github" href="#" target="_blank"></a></p>
      </div>
    </div>
    <script>
        function decrypt(data) {
          return atob(data);
        }
        document.getElementById('author').innerText = decrypt('U1VNQU4gU0FIQQ==');
        document.getElementById('github').innerText = decrypt('aHR0cHM6Ly9naXRodWIuY29tL2NpcmN1aXRvLXN1bWFuLzc0SEM1OTVsZWRtYXRyaXhsaWJyYXJ5');
        document.getElementById('github').href = decrypt('aHR0cHM6Ly9naXRodWIuY29tL2NpcmN1aXRvLXN1bWFuLzc0SEM1OTVsZWRtYXRyaXhsaWJyYXJ5');
      </script>

</body>
</html>
  )rawliteral";


  String text = "<p>Text received successfully. Go back to <a href='/'>home</a>.</p>";
  String error = "<p>Bad request. Go back to <a href='/'>home</a>.</p>"; 


  #endif //