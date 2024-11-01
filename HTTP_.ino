#include <WiFi.h>
#include <WebServer.h>
#define JIDing 21

// 连接WIFI的名字以及密码
const char* ssid = "Test01";
const char* password = "55556666";

// 创建Web服务器对象，监听在端口 80
WebServer server(80);

// 状态变量
bool ledState = false;

// 定义按钮点击事件
void handleButton() {
  // 切换 LED 状态
  ledState = !ledState;
  digitalWrite(JIDing, ledState ? HIGH : LOW);
  
  // 在页面上显示切换后的状态
  server.send(200, "text/html", "<h1>LED 状态: " + String(ledState ? "开" : "关") + "</h1>");
  
  // 记录切换状态
  Serial.println(ledState ? "Button01" : "Button02");
}

// 网页搭建
void handleRoot() {

  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<title>ESP32 切换测试</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css'>";
  html += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css'>";
  html += "<style>";
  html += "  body { background-color:rgb(255, 255, 255) ; margin: 0; padding: 0; }";
  html += "  .container { max-width: 800px; margin: auto; padding: 20px; background-color: rgb(255, 255, 255) }";
  html += "  .card { margin-top: 20px; background-color: rgb(198, 198, 198)}";
  html += "  .card-body { margin-top: 20px; background-color:rgb(198, 198, 198)}";
  html += "  .btn { transition: transform 0.2s ease-out; }";
  html += "  .btn:hover { transform: scale(1.1); }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<div class='container'>";
  html += "<div class='card'>";
  html += "<div class='card-body'>";
  html += "<h5 class='card-title'>ESP32 切换测试</h5>";
  html += "<p class='card-text'>点击切换按钮来改变 LED 状态:</p>";
  html += "<div class='d-flex align-items-center'>";
  html += "<i class='fas fa-lightbulb' style='color:" + String(ledState ? "green" : "black") + "; font-size: 2em;'></i>";
  html += "<label class='switch ml-3'>";
  html += "<input type='checkbox' " + String(ledState ? "checked" : "") + " onclick='toggleState()'>";
  html += "<span class='slider round'></span>";
  html += "</label>";
  html += "</div>";
  html += "</div>";
  html += "</div>";
  html += "</div>";
  html += "<script>";
  html += "function toggleState() {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/toggle', true);";
  html += "  xhr.onreadystatechange = function() {";
  html += "    if (xhr.readyState === 4 && xhr.status === 200) {";
  html += "      var newState = JSON.parse(xhr.responseText).state;";
  html += "      var icon = document.querySelector('.fa-lightbulb');";
  html += "      icon.style.color = newState ? 'green' : 'black';";
  html += "      var checkbox = document.querySelector('input[type=checkbox]');";
  html += "      checkbox.checked = newState;";
  html += "    }";
  html += "  };";
  html += "  xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body>";
  html += "</html>";

//  String html = "<!DOCTYPE html>\n";
//   html += "<html>\n";
//   html += "<head>\n";
//   html += "<meta charset='UTF-8'>\n";
//   html += "<title>ESP32 控制面板</title>\n";
//   html += "<meta name='viewport' content='width=device-width, initial-scale=1'>\n";
//   html += "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css'>\n";
//   html += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css'>\n";
//   html += "<style>\n";
//   html += "  body { background-color:#f4f4f4; margin: 0; padding: 0; }\n";
//   html += "  .container { max-width: 800px; margin: auto; padding: 20px; background-color: #fff; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }\n";
//   html += "  .card { margin-top: 20px; border-radius: 10px; }\n";
//   html += "  .btn { transition: transform 0.2s ease-out; }\n";
//   html += "  .btn:hover { transform: scale(1.1); }\n";
//   html += "  .switch input[type=checkbox] { display:none; }\n";
//   html += "  .switch .slider { position:relative; display:inline-block; width:60px; height:34px; }\n";
//   html += "  .switch .slider:before { position:absolute; content:\"\"; height:26px; width:26px; left:4px; bottom:4px; background-color:white; transition:0.4s; }\n";
//   html += "  .switch input:checked+.slider:before { transform:translateX(26px); }\n";
//   html += "  .switch .slider.round { border-radius:34px; }\n";
//   html += "  .switch .slider.round:before { border-radius:50%; }\n";
//   html += "  .brightness-slider { margin-top: 20px; }\n";
//   html += "</style>\n";
//   html += "</head>\n";
//   html += "<body>\n";
//   html += "<div class='container'>\n";
//   html += "<div class='card p-3'>\n";
//   html += "<div class='card-body text-center'>\n";
//   html += "<h5 class='card-title'>ESP32 控制面板</h5>\n";
//   html += "<p class='card-text'>使用以下控件来管理 LED 状态:</p>\n";
//   html += "<div class='d-flex justify-content-center align-items-center mb-4'>\n";
//   html += "<i class='fas fa-lightbulb' id='lightIcon' style='color:#ccc; font-size: 2em;'></i>\n";
//   html += "<label class='switch ml-3'>\n";
//   html += "<input type='checkbox' id='lightSwitch' onclick='toggleState()' " + String(ledState ? "checked" : "") + ">\n";
//   html += "<span class='slider round'></span>\n";
//   html += "</label>\n";
//   html += "</div>\n";
//   html += "<div class='brightness-slider'>\n";
//   html += "<h6 class='text-center mb-2'>调节亮度:</h6>\n";
//   html += "<input type='range' min='0' max='100' value='50' class='form-control-range' id='brightnessSlider' oninput='setBrightness(this.value)'>\n";
//   html += "</div>\n";
//   html += "<div class='d-flex justify-content-around mt-4'>\n";
//   html += "<button class='btn btn-primary btn-lg' onclick='alert(\'Feature A activated\')'>功能 A</button>\n";
//   html += "<button class='btn btn-secondary btn-lg' onclick='alert(\'Feature B activated\')'>功能 B</button>\n";
//   html += "<button class='btn btn-success btn-lg' onclick='alert(\'Feature C activated\')'>功能 C</button>\n";
//   html += "</div>\n";
//   html += "</div>\n";
//   html += "</div>\n";
//   html += "</div>\n";
//   html += "<script>\n";
//   html += "function toggleState() {\n";
//   html += "  var xhr = new XMLHttpRequest();\n";
//   html += "  xhr.open('GET', '/toggle', true);\n";
//   html += "  xhr.onreadystatechange = function() {\n";
//   html += "    if (xhr.readyState === 4 && xhr.status === 200) {\n";
//   html += "      var newState = JSON.parse(xhr.responseText).state;\n";
//   html += "      var icon = document.getElementById('lightIcon');\n";
//   html += "      icon.style.color = newState ? '#28a745' : '#ccc';\n";
//   html += "      var checkbox = document.getElementById('lightSwitch');\n";
//   html += "      checkbox.checked = newState;\n";
//   html += "    }\n";
//   html += "  };\n";
//   html += "  xhr.send();\n";
//   html += "}\n";
//   html += "function setBrightness(value) {\n";
//   html += "  var xhr = new XMLHttpRequest();\n";
//   html += "  xhr.open('GET', '/brightness?level=' + value, true);\n";
//   html += "  xhr.onreadystatechange = function() {\n";
//   html += "    if (xhr.readyState === 4 && xhr.status === 200) {\n";
//   html += "      alert('亮度设置为 ' + value + '%');\n";
//   html += "    }\n";
//   html += "  };\n";
//   html += "  xhr.send();\n";
//   html += "}\n";
//   html += "</script>\n";
//   html += "</body>\n";
//   html += "</html>";
  server.send(200, "text/html", html);
}

// 处理 AJAX 请求更新状态
void handleToggle() {
  // 切换 LED 状态
  ledState = !ledState;
  digitalWrite(JIDing, ledState ? HIGH : LOW);
  Serial.println(111);
  // 返回新的状态
  server.send(200, "application/json", "{\"state\": " + String(ledState ? "true" : "false") + "}");
}

// 异常函数
void handleNotFound() {
  // 如果客户端请求的资源不存在，则发送一个 HTTP 404 Not Found 响应
  server.send(404, "text/plain", "Not found");
}

// void handleBrightness() {
//   int level = server.arg("level").toInt();
//   // 这里假设你有一个方法来设置 LED 的亮度
//   // setBrightness(level);
//   Serial.print("Brightness set to: ");
//   Serial.println(level);
//   server.send(200, "text/plain", "Brightness set to " + String(level));
// }


void setup() {
  Serial.begin(115200);
  pinMode(JIDing, OUTPUT);

  //  server.on("/brightness", handleBrightness);  // 设置处理亮度调节的函数

  // 连接到 Wi-Fi 网络
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  // 打印连接 IP
  Serial.println("\nConnected to the WiFi network!");
  Serial.print("ESP32's IP address: ");
  Serial.println(WiFi.localIP());

  // 注册路由处理函数
  server.on("/", handleRoot);          // 设置根目录的处理函数
  server.on("/toggle", handleToggle);  // 设置处理 AJAX 请求的函数
  server.onNotFound(handleNotFound);   // 设置处理未找到资源的函数

  // 初始化服务器
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();               // 处理客户端请求
}