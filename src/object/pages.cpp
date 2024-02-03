//=============================================================================
//  pages
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 30 January 2024
//  file:   pages.cpp
//=============================================================================

#include "pages.h"

const char index_html[] = R"rawliteral( <html>
<head>
    <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
    <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } </style>
</head>
<body>
    <h1>ESP-Webserver</h1>
    <form action='/load'>
        <h2>Overview</h2>
        <div>Version: 1.0</div> <input type='submit' value='ESP Start'>
    </form>
    <div>
        <table></table>
        <hr>
        <table>
            <tbody>
                <tr>
                    <th>Aktuelle Uhrzeit</th>
                    <td style="width:20px;white-space:nowrap">%%TIME%%</td>
                </tr>
                <tr>
                    <th>Motor Drehrichtung</th>
                    <td style="width:20px;white-space:nowrap">%%ENGINE%%</td>
                </tr>
                <tr>
                    <th>Endlagenschalter Oben</th>
                    <td style="width:20px;white-space:nowrap">%%ENDUP%%</td>
                </tr>
                <tr>
                    <th>Endlagenschalter Unten</th>
                    <td style="width:20px;white-space:nowrap">%%ENDDOWN%%</td>
                </tr>
                <tr>
                    <th>Lichtsensor</th>
                    <td style="width:20px;white-space:nowrap">%%LIGHT%%</td>
                </tr>
                <tr>
                    <th>WLAN</th>
                    <td style="width:20px;white-space:nowrap">%%WIFI%%</td>
                </tr>
            </tbody>
        </table>
        <hr>
        <table></table>
    </div>
    <form class="btn" action='/config'> <button>Konfiguration</button> </form>
    <form class="btn" action='/action'> <button>Aktionen</button> </form>
    <form class="btn" action='/info'> <button>Informationen</button> </form>
    <form class="btn" action='/update'> <button>Firmware Upgrade</button> </form>
    <form class="btn btn-red" action='/reset'> <button>Neustarten</button> </form>
</body>

</html> )rawliteral";

const char configMenu_html[] = R"rawliteral( <html>
<head>
    <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
    <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } </style>
</head>
<body>
    <h1>ESP-Webserver</h1>
    <h2>Konfiguration</h2>
    <div>Version: 1.0</div>
    <p></p>
    <form class="btn" action='/cw'> <button>WLAN</button> </form>
    <form class="btn" action='/co'> <button>Ausgang Zuordnen</button> </form>
    <form class="btn" action='/cc1'> <button>Steuerung Zeit 1</button> </form>
    <form class="btn" action='/cc2'> <button>Steuerung Zeit 2</button> </form>
    <form class="btn" action='/ct'> <button>Aktuelle Zeit</button> </form>
    <p></p>
    <form class="btn" action='/'> <button>Main Menu</button> </form>
</body>

</html> )rawliteral";

const char configWLAN_html[] = R"rawliteral(
    <html>
    <head>
        <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
        <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style>
        </head>
    <body>
        <h1>ESP-Webserver</h1>
        <h2>WLAN - Einstellungen</h2>
        <form action='/saveWifi'>
            <div>SSID</div><input type='text' name='ssid'><br>
            <div>Password</div><input type='password' name='password'><br>
            <input class="btn-action" type='submit' value='Sichern WiFi'>
        </form>
        <p><hr></p>
        <form class="btn" action='/config'>
            <button>Config Menu</button>
        </form>
        
    </body>

    </html>
)rawliteral";

const char configOutput_html[] = R"rawliteral(
    <html> <head> <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'> <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style> </head> <body> <h1>ESP-Webserver</h1> <h2>Ausgang - Einstellungen</h2> <hr> <h3>Aktuelle Drehrichtung</h3> <table> <tbody> <tr> <th>M1</th> <td style="width:20px;white-space:nowrap">%%M1%%</td> </tr> <tr> <th>M2</th> <td style="width:20px;white-space:nowrap">%%M2%%</td> </tr> </tbody> </table> <p><hr></p> <form action='/saveOutput'> <div> <label for="engine1">Konfiguration der Drehrichtung</label> <select id="engine1" name="engine1"> <option value="0">M1 = Linkslauf</option> <option value="1">M1 = Rechtslauf</option> </select> <input class="btn-action" type='submit' value='Sichern Motordrehrichtung'> </div> </form> <p><hr></p> <h3>Drehrichtungstest</h3> <div class="form-container"> <form action='/setE1w'> <input class="btn-action" type='submit' value='Linkslauf'> <div>Status: %%STATUSE1%%</div> </form> <form action='/setE2w'> <input class="btn-action" type='submit' value='Rechtslauf'> <div>Status: %%STATUSE2%%</div> </form> </div> <p><hr></p> <form class="btn" action='/config'> <button>Config Menu</button> </form> </body> </html>
)rawliteral";

const char configControl1_html[] = R"rawliteral(
    <html> <head> <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'> <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style> </head> <body> <h1>ESP-Webserver</h1> <h2>Steuerung - Einstellungen</h2> <form action='/saveTime1'> <h2>Zeit - Einstellung 1</h2> <div class="form-container"> <div>Stunde</div><input type='text' name='hour' %%h1%%><br> <div>Minute</div><input type='text' name='min' %%m1%%><br> </div> <div class="form-container"> <div> <label for="engine1">Wähle eine Drehrichtung</label> <select id="engine1" name="engine1"> <option value="0" %%s11%%>Linkslauf</option> <option value="1" %%s12%%>Rechtslauf</option> </select> </div> <div> <label for="limit1">Wähle ein Endlagenschalter</label> <select id="limit1" name="limit1"> <option value="0" %%s13%%>Endlage Oben</option> <option value="1" %%s14%%>Endlage Unten</option> </select> </div> </div> <div> <label for="signal">Signal zur Unterbrechung</label> <select id="signal1" name="signal1"> <option value="0" %%s15%%>LOW-Signal</option> <option value="1" %%s16%%>HIGH-Signal</option> </select> </div> </div> <input class="btn-action" type='submit' value='Sichern'> </form>  <p><hr></p> <form class="btn" action='/config'> <button>Config Menu</button> </form> </body> </html>
)rawliteral";

const char configControl2_html[] = R"rawliteral(
    <html> <head> <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'> <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style> </head> <body> <h1>ESP-Webserver</h1> <h2>Steuerung - Einstellungen</h2> <form action='/saveTime2'> <h2>Zeit - Einstellung 2</h2> <div class="form-container"> <div>Stunde</div><input type='text' name='hour' %%h2%%><br> <div>Minute</div><input type='text' name='min' %%m2%%><br> </div> <div class="form-container"> <div> <label for="engine2">Wähle eine Drehrichtung</label> <select id="engine2" name="engine2"> <option value="0" %%s21%%>Linkslauf</option> <option value="1" %%s22%%>Rechtslauf</option> </select> </div> <div> <label for="limit2">Wähle ein Endlagenschalter</label> <select id="limit2" name="limit2"> <option value="0" %%s23%%>Endlage Oben</option> <option value="1" %%s24%%>Endlage Unten</option> </select> </div> </div> <div> <label for="signal">Signal zur Unterbrechung</label> <select id="signal2" name="signal2"> <option value="0" %%s25%%>LOW-Signal</option> <option value="1" %%s26%%>HIGH-Signal</option> </select> </div> </div> <input class="btn-action" type='submit' value='Sichern'> </form> <p><hr></p> <form class="btn" action='/config'> <button>Config Menu</button> </form> </body> </html>
)rawliteral";

const char configTime_html[] = R"rawliteral(
    <html>
    <head>
        <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
        <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style>
        </head>
    <body>
        <h1>ESP-Webserver</h1>
        <h2>Aktuelle Zeit - Einstellungen</h2>
        <p><hr></p>
        <table>
            <tbody>
                <tr>
                    <th>Aktuelle Uhrzeit</th>
                    <td style="width:20px;white-space:nowrap">%%TIME%%</td>
                </tr>
            </tbody>
        </table>
        <p><hr></p>
        <form action='/setCTime'>
            <div class="form-container"> 
                <div>Stunde</div><input type='text' name='hour'><br>
                <div>Minute</div><input type='text' name='min'><br>
            </div>

            <input class="btn-action" type='submit' value='Sichern Zeit'>
        </form>
        <p><hr></p>
        <form class="btn" action='/config'>
            <button>Config Menu</button>
        </form>
        
    </body>

    </html>
)rawliteral";

const char config_html[] = R"rawliteral(
    <html>
    <head>
        <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
        <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style>
        </head>
    <body>
        <h1>ESP-Webserver</h1>
        <h2>Konfiguration</h2>
        <div>Version: 1.0
        <form action='/saveWifi'>
            <h2>WLAN - Einstellunge</h2>
            <div>SSID</div><input type='text' name='ssid'><br>
            <div>Password</div><input type='password' name='password'><br>
            <input class="btn-action" type='submit' value='Sichern WiFi'>
        </form>
        <p><hr></p>
        
        <p><hr></p>
        
        <p><hr></p>
        <form class="btn" action='/'>
            <button>Main Menu</button>
        </form>
        
    </body>

    </html>
)rawliteral";

const char action_html[] = R"rawliteral(
    <html>
    <head>
        <meta charset="utf-8" name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
        <style> body { text-align: center; background-color: cornflowerblue; max-width: 340px; margin-left: auto; margin-right: auto; } th { text-align: left; padding-right: 32px; } div, input { margin: 5px; } input { border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .btn-action { border: 0; cursor: pointer; transition-duration: 0.4s; background: orange; } .btn-action:hover { background: darkorange; } .btn>button { border: 0; border-radius: 0.3rem; line-height: 2.4rem; font-size: 1.2rem; width: 100%; cursor: pointer; transition-duration: 0.4s; } .btn>button:hover { background: goldenrod; } .btn-red>button { background: #d43535; } .btn-red>button:hover { background: darkred; color: white; } .form-container { display: flex; justify-content: space-between; } </style>
        </head>
    <body>
        <h1>ESP-Webserver</h1>
        <h2>Konfiguration</h2>
        <div>Version: 1.0
        <div class="form-container">
            <form action='/setE1'>
                <input class="btn-action" type='submit' value='Linkslauf'>
                <div>Status: %%STATUSE1%%</div>
            </form>
            <form action='/setE2'>
                <input class="btn-action" type='submit' value='Rechtslauf'>
                <div>Status: %%STATUSE2%%</div>
            </form>
        </div>
        <p><hr></p>
                <div class="form-container">
            <form action='/setL1'>
                <input class="btn-action" type='submit' value='Lampe Rot'>
                <div>Status: %%STATUSL1%%</div>
            </form>
            <form action='/setL2'>
                <input class="btn-action" type='submit' value='Lampe Orange'>
                <div>Status: %%STATUSL2%%</div>
            </form>
            <form action='/setL3'>
                <input class="btn-action" type='submit' value='Lampe Grün'>
                <div>Status: %%STATUSL3%%</div>
            </form>
        </div>
        <p><hr></p>
        <form class="btn" action='/'>
            <button>Main Menu</button>
        </form>
        
    </body>

    </html>
)rawliteral";

//=============================================================================
// End of File
//=============================================================================