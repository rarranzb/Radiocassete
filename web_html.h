// =============================================================
// web_html.h -- Interfaz web embebida en PROGMEM
// =============================================================
//
// Aqui vive todo el HTML/CSS/JavaScript de la Single Page App.
// Edita este archivo para cambiar la interfaz de usuario.
//
// Incluido por web_server.ino mediante #include "web_html.h"
// =============================================================
#pragma once

static const char INDEX_HTML[] PROGMEM = R"HTMLEOF(<!DOCTYPE html><html lang='es'><head>
<meta charset='utf-8'>
<meta name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'>
<title>Radiocassete</title>
<link rel='icon' type='image/svg+xml' href='data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA2NCA2NCI+CiAgPCEtLSBGb25kbyAtLT4KICA8cmVjdCB3aWR0aD0iNjQiIGhlaWdodD0iNjQiIHJ4PSIxMCIgZmlsbD0iIzNhMWMwNiIvPgogIDwhLS0gQ3VlcnBvIGNhc3NldHRlIC0tPgogIDxyZWN0IHg9IjYiIHk9IjE2IiB3aWR0aD0iNTIiIGhlaWdodD0iMzIiIHJ4PSI0IiBmaWxsPSIjYzg5MjJhIi8+CiAgPHJlY3QgeD0iOCIgeT0iMTgiIHdpZHRoPSI0OCIgaGVpZ2h0PSIyOCIgcng9IjMiIGZpbGw9IiMyYTE0MDgiLz4KICA8IS0tIFZlbnRhbmEgY2VudHJhbCAtLT4KICA8cmVjdCB4PSIxOCIgeT0iMjIiIHdpZHRoPSIyOCIgaGVpZ2h0PSIxNiIgcng9IjIiIGZpbGw9IiMxYTBjMDQiLz4KICA8IS0tIEJvYmluYXMgLS0+CiAgPGNpcmNsZSBjeD0iMjYiIGN5PSIzMCIgcj0iNSIgZmlsbD0iIzNhMWMwNiIgc3Ryb2tlPSIjYzg5MjJhIiBzdHJva2Utd2lkdGg9IjEuNSIvPgogIDxjaXJjbGUgY3g9IjI2IiBjeT0iMzAiIHI9IjIiIGZpbGw9IiNjODkyMmEiLz4KICA8Y2lyY2xlIGN4PSIzOCIgY3k9IjMwIiByPSI1IiBmaWxsPSIjM2ExYzA2IiBzdHJva2U9IiNjODkyMmEiIHN0cm9rZS13aWR0aD0iMS41Ii8+CiAgPGNpcmNsZSBjeD0iMzgiIGN5PSIzMCIgcj0iMiIgZmlsbD0iI2M4OTIyYSIvPgogIDwhLS0gQ2ludGEgLS0+CiAgPGxpbmUgeDE9IjIxIiB5MT0iMzYiIHgyPSI0MyIgeTI9IjM2IiBzdHJva2U9IiNjODkyMmEiIHN0cm9rZS13aWR0aD0iMSIvPgogIDwhLS0gVG9ybmlsbG9zIGVzcXVpbmFzIC0tPgogIDxjaXJjbGUgY3g9IjEyIiBjeT0iMjIiIHI9IjIiIGZpbGw9IiM2YTNlMDgiLz4KICA8Y2lyY2xlIGN4PSI1MiIgY3k9IjIyIiByPSIyIiBmaWxsPSIjNmEzZTA4Ii8+CiAgPGNpcmNsZSBjeD0iMTIiIGN5PSI0MiIgcj0iMiIgZmlsbD0iIzZhM2UwOCIvPgogIDxjaXJjbGUgY3g9IjUyIiBjeT0iNDIiIHI9IjIiIGZpbGw9IiM2YTNlMDgiLz4KPC9zdmc+Cg=='>
<link rel='apple-touch-icon' href='data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA2NCA2NCI+CiAgPCEtLSBGb25kbyAtLT4KICA8cmVjdCB3aWR0aD0iNjQiIGhlaWdodD0iNjQiIHJ4PSIxMCIgZmlsbD0iIzNhMWMwNiIvPgogIDwhLS0gQ3VlcnBvIGNhc3NldHRlIC0tPgogIDxyZWN0IHg9IjYiIHk9IjE2IiB3aWR0aD0iNTIiIGhlaWdodD0iMzIiIHJ4PSI0IiBmaWxsPSIjYzg5MjJhIi8+CiAgPHJlY3QgeD0iOCIgeT0iMTgiIHdpZHRoPSI0OCIgaGVpZ2h0PSIyOCIgcng9IjMiIGZpbGw9IiMyYTE0MDgiLz4KICA8IS0tIFZlbnRhbmEgY2VudHJhbCAtLT4KICA8cmVjdCB4PSIxOCIgeT0iMjIiIHdpZHRoPSIyOCIgaGVpZ2h0PSIxNiIgcng9IjIiIGZpbGw9IiMxYTBjMDQiLz4KICA8IS0tIEJvYmluYXMgLS0+CiAgPGNpcmNsZSBjeD0iMjYiIGN5PSIzMCIgcj0iNSIgZmlsbD0iIzNhMWMwNiIgc3Ryb2tlPSIjYzg5MjJhIiBzdHJva2Utd2lkdGg9IjEuNSIvPgogIDxjaXJjbGUgY3g9IjI2IiBjeT0iMzAiIHI9IjIiIGZpbGw9IiNjODkyMmEiLz4KICA8Y2lyY2xlIGN4PSIzOCIgY3k9IjMwIiByPSI1IiBmaWxsPSIjM2ExYzA2IiBzdHJva2U9IiNjODkyMmEiIHN0cm9rZS13aWR0aD0iMS41Ii8+CiAgPGNpcmNsZSBjeD0iMzgiIGN5PSIzMCIgcj0iMiIgZmlsbD0iI2M4OTIyYSIvPgogIDwhLS0gQ2ludGEgLS0+CiAgPGxpbmUgeDE9IjIxIiB5MT0iMzYiIHgyPSI0MyIgeTI9IjM2IiBzdHJva2U9IiNjODkyMmEiIHN0cm9rZS13aWR0aD0iMSIvPgogIDwhLS0gVG9ybmlsbG9zIGVzcXVpbmFzIC0tPgogIDxjaXJjbGUgY3g9IjEyIiBjeT0iMjIiIHI9IjIiIGZpbGw9IiM2YTNlMDgiLz4KICA8Y2lyY2xlIGN4PSI1MiIgY3k9IjIyIiByPSIyIiBmaWxsPSIjNmEzZTA4Ii8+CiAgPGNpcmNsZSBjeD0iMTIiIGN5PSI0MiIgcj0iMiIgZmlsbD0iIzZhM2UwOCIvPgogIDxjaXJjbGUgY3g9IjUyIiBjeT0iNDIiIHI9IjIiIGZpbGw9IiM2YTNlMDgiLz4KPC9zdmc+Cg=='>
<link href='https://fonts.googleapis.com/css2?family=Pacifico&family=Courier+Prime:wght@400;700&display=swap' rel='stylesheet'>
<style>
:root{
  --g1:#f0c060;--g2:#c8922a;--g3:#a06818;--g4:#6a3e08;--g5:#3a2004;
  --g-sh:#ffe090;--am:#ff9020;--am2:#ffb040;
  --tx:#e8d090;--tx2:#a07830;--tx3:#604818;--d2:#120c04;
  --mono:'Courier Prime',monospace;--title:'Pacifico',cursive;
}
*{box-sizing:border-box;margin:0;padding:0;}
html{min-height:100%;background:
  repeating-linear-gradient(175deg,transparent 0,transparent 8px,rgba(0,0,0,.18) 8px,rgba(0,0,0,.18) 9px,transparent 9px,transparent 22px,rgba(0,0,0,.10) 22px,rgba(0,0,0,.10) 23px),
  linear-gradient(180deg,#6a3814 0%,#4a2408 30%,#3a1c06 60%,#4e2810 100%);}
body{font-family:var(--mono);color:var(--tx);max-width:520px;margin:0 auto;padding-bottom:60px;padding-top:135px;}

/* ═══ BOTONES FÍSICOS ═══ */
.pbtn{display:inline-flex;flex-direction:column;align-items:center;justify-content:center;gap:5px;
  padding:10px 14px;min-width:52px;border-radius:6px;cursor:pointer;user-select:none;
  font-family:var(--mono);font-size:10px;font-weight:700;letter-spacing:2px;text-transform:uppercase;
  border-top:1.5px solid transparent;border-left:1.5px solid transparent;
  border-right:1.5px solid transparent;border-bottom:5px solid transparent;
  box-shadow:0 4px 10px rgba(0,0,0,.7);transition:transform 80ms,border-bottom-width 80ms,box-shadow 80ms;position:relative;}
.pbtn::before{content:'';position:absolute;top:0;left:0;right:0;height:40%;border-radius:5px 5px 0 0;
  background:linear-gradient(180deg,rgba(255,255,255,.09) 0%,transparent 100%);pointer-events:none;}
.pbtn:active{transform:translateY(4px);border-bottom-width:1px!important;box-shadow:0 1px 4px rgba(0,0,0,.5);}
.pbtn-brass{color:var(--d2);text-shadow:0 1px 0 rgba(255,230,140,.4);
  background:linear-gradient(180deg,var(--g3) 0%,var(--g2) 18%,var(--g1) 36%,var(--g-sh) 46%,var(--g1) 56%,var(--g2) 72%,var(--g4) 100%);
  border-top-color:var(--g-sh);border-left-color:var(--g2);border-right-color:var(--g4);border-bottom-color:var(--g5);}
.pbtn-dark{color:var(--tx);
  background:repeating-linear-gradient(180deg,transparent 0,transparent 3px,rgba(255,255,255,.028) 3px,rgba(255,255,255,.028) 4px),
    linear-gradient(180deg,#3a2a10 0%,#2a1c08 20%,#1e1206 55%,#160e04 100%);
  border-top-color:rgba(255,200,80,.25);border-left-color:rgba(255,200,80,.12);
  border-right-color:rgba(0,0,0,.5);border-bottom-color:var(--g5);}
.pbtn-dark:hover{color:var(--g1);}
.pbtn-red{color:#d05050;
  background:linear-gradient(180deg,#4a1408 0%,#3a0c04 25%,#2c0802 65%,#200402 100%);
  border-top-color:rgba(255,80,60,.2);border-left-color:rgba(255,80,60,.1);
  border-right-color:rgba(0,0,0,.5);border-bottom-color:#2a0802;}
.pbtn-red:hover{color:#e86060;}
.pbtn-full{width:100%;margin-top:10px;}
.pbtn-row{display:flex;gap:10px;}.pbtn-row .pbtn{flex:1;}
.pbtn-dark.adv-open{transform:translateY(4px);border-bottom-width:1px!important;box-shadow:0 1px 4px rgba(0,0,0,.5);color:var(--g1);}

/* ═══ MINI VU (header) ─ 6 LEDs, φ-proportioned ═══ */
.hdr-vu{display:flex;gap:5px;align-items:flex-end;flex-shrink:0;margin-left:auto;}
.hdr-vu-col{display:flex;flex-direction:column;align-items:center;}
.hdr-vu-ch{font-family:var(--mono);font-size:7px;font-weight:700;color:var(--tx3);margin-top:2px;line-height:1;}
.hdr-vu-bar{display:flex;flex-direction:column-reverse;gap:1.5px;}
.hdr-vu-bar .vs{width:8px!important;height:8px!important;border-radius:50%!important;flex:none!important;}

/* ═══ HEADER ═══ */
.hdr{background:repeating-linear-gradient(175deg,transparent 0,transparent 7px,rgba(0,0,0,.2) 7px,rgba(0,0,0,.2) 8px,transparent 8px,transparent 20px),
  linear-gradient(180deg,#7a4818 0%,#5a3010 30%,#4a2408 70%,#5e3414 100%);
  border-top:3.5px solid;border-image:linear-gradient(90deg,var(--g5),var(--g2),var(--g-sh),var(--g2),var(--g5)) 1;
  box-shadow:0 6px 24px rgba(0,0,0,.8);position:fixed;top:0;left:0;right:0;z-index:100;max-width:520px;margin:0 auto;}
.screw-row{display:flex;justify-content:space-between;padding:10px 12px 0;}
.screw{width:13px;height:13px;border-radius:50%;flex-shrink:0;
  background:radial-gradient(circle at 35% 30%,var(--g1) 0%,var(--g2) 30%,var(--g4) 70%,var(--g5) 100%);
  box-shadow:inset 1px 1px 2px rgba(255,230,140,.35),inset -1px -1px 2px rgba(0,0,0,.6),0 1px 4px rgba(0,0,0,.7);position:relative;}
.screw::before,.screw::after{content:'';position:absolute;background:rgba(0,0,0,.55);border-radius:1px;}
.screw::before{top:50%;left:20%;right:20%;height:1.5px;transform:translateY(-50%);}
.screw::after{left:50%;top:20%;bottom:20%;width:1.5px;transform:translateX(-50%);}
.logo-area{padding:10px 18px 16px;display:flex;align-items:center;gap:14px;}
.copper-plate{background:linear-gradient(135deg,var(--g5) 0%,var(--g4) 15%,var(--g3) 28%,var(--g2) 40%,var(--g1) 50%,var(--g-sh) 54%,var(--g1) 60%,var(--g2) 70%,var(--g4) 85%,var(--g5) 100%);
  padding:7px 14px;border-radius:3px;font-family:var(--title);font-size:12px;font-weight:700;letter-spacing:2px;color:var(--d2);
  text-shadow:0 1px 0 rgba(255,220,140,.5);box-shadow:inset 0 1px 0 rgba(255,220,140,.4),inset 0 -1px 0 rgba(0,0,0,.5),0 2px 8px rgba(0,0,0,.6);}
.logo-title{font-family:var(--title);font-size:37px;font-weight:400;color:#e0c880;text-shadow:0 1px 6px rgba(0,0,0,.9);line-height:1;}
.logo-sub{font-family:var(--mono);font-size:10px;color:var(--tx2);letter-spacing:2px;margin-top:2px;}
.logo-ver{font-family:var(--mono);font-size:8px;color:var(--tx3);letter-spacing:1px;margin-top:1px;opacity:.6;}
nav{display:flex;gap:4px;padding:0 4px;justify-content:center;}
nav a{font-family:var(--mono);font-size:11px;font-weight:700;letter-spacing:2px;text-transform:uppercase;
  color:var(--tx3);text-decoration:none;cursor:pointer;padding:8px 14px 7px;border-radius:4px 4px 0 0;flex:1;text-align:center;
  background:linear-gradient(180deg,#7a4018 0%,#6a3010 40%,#3e1e08 100%);
  border:1.5px solid var(--g5);border-bottom:none;
  box-shadow:inset 0 1px 0 rgba(255,210,100,.12),inset 0 -2px 5px rgba(0,0,0,.5);transition:color .2s;}
nav a:hover{color:var(--g2);}
nav a.active{color:var(--am2);background:linear-gradient(180deg,#3a2008 0%,#2a1404 60%,#200e02 100%);border-color:var(--g3);
  box-shadow:inset 0 1px 0 rgba(255,210,100,.18),0 0 16px rgba(255,144,32,.15);position:relative;}
nav a.active::after{content:'';display:block;position:absolute;bottom:-1px;left:0;right:0;height:2px;
  background:linear-gradient(90deg,transparent,var(--g2),var(--g1),var(--g2),transparent);}
.mute-btn{margin-left:auto;background:linear-gradient(180deg,#3a1808 0%,#2a0e04 100%);
  border:1.5px solid var(--g5);border-radius:4px;color:var(--tx3);padding:8px 10px 7px;font-family:var(--mono);font-size:11px;font-weight:700;letter-spacing:1px;text-transform:uppercase;text-decoration:none;cursor:pointer;transition:all .2s;flex-shrink:0;}
.mute-btn:hover{color:#ccc;}
.mute-btn.muted{background:linear-gradient(180deg,#8c1a1a 0%,#5a0e0e 100%);
  color:#ff6060;border-color:#9c2020;box-shadow:0 0 12px rgba(200,30,30,.4),inset 0 1px 0 rgba(255,100,100,.2);
  animation:mutePulse 1.5s ease-in-out infinite;}
@keyframes mutePulse{0%,100%{box-shadow:0 0 12px rgba(200,30,30,.3),inset 0 1px 0 rgba(255,100,100,.2);}
  50%{box-shadow:0 0 20px rgba(220,40,40,.6),inset 0 1px 0 rgba(255,100,100,.3);}}

/* ═══ FACE ═══ */
.face{background:repeating-linear-gradient(45deg,transparent 0,transparent 13px,rgba(0,0,0,.14) 13px,rgba(0,0,0,.14) 14px),
  repeating-linear-gradient(-45deg,transparent 0,transparent 13px,rgba(0,0,0,.14) 13px,rgba(0,0,0,.14) 14px),
  linear-gradient(180deg,#3e1c06 0%,#321408 40%,#2a1004 70%,#361808 100%);
  border-left:3px solid var(--g5);border-right:3px solid var(--g5);border-bottom:3px solid var(--g5);
  padding:18px 16px 24px;overflow:visible;box-shadow:inset 0 0 40px rgba(0,0,0,.4),0 8px 32px rgba(0,0,0,.9);}
.page{display:none;}.page.active{display:block;}
.panel{background:linear-gradient(180deg,#2a1808 0%,#1e1004 50%,#241408 100%);
  border-radius:6px;padding:16px;margin-bottom:16px;border:1.5px solid var(--g4);overflow:visible;
  box-shadow:inset 0 2px 8px rgba(0,0,0,.6),0 2px 12px rgba(0,0,0,.4);}
.panel-title{font-family:var(--mono);font-size:10px;font-weight:700;letter-spacing:3px;text-transform:uppercase;
  color:var(--g2);margin-bottom:14px;padding-bottom:10px;border-bottom:1px solid var(--g4);
  text-shadow:0 0 12px rgba(200,146,42,.45);}

/* STATUS */
.sr{display:flex;justify-content:space-between;align-items:center;padding:8px 0;border-bottom:1px solid rgba(160,104,48,.2);}
.sr:last-child{border-bottom:none;}
.sl{font-family:var(--mono);font-size:10px;letter-spacing:2px;text-transform:uppercase;color:var(--tx3);}
.sv{font-family:var(--mono);font-size:12px;color:var(--tx);}
.on{color:#e8c060;text-shadow:0 0 8px rgba(232,192,96,.6);}.off{color:#483010;}
.hot{color:var(--am);text-shadow:0 0 10px rgba(255,144,32,.7);}
.led{display:inline-block;width:10px;height:10px;border-radius:50%;margin-right:6px;vertical-align:middle;}
.led-g{background:radial-gradient(circle at 35% 30%,#ffee80,#d4a020);box-shadow:0 0 8px rgba(212,160,32,.9),0 0 16px rgba(212,160,32,.4);animation:lp 2.5s ease-in-out infinite;}
.led-o{background:radial-gradient(circle at 35% 30%,#ffd060,#ff8010);box-shadow:0 0 10px rgba(255,144,32,1),0 0 20px rgba(255,144,32,.5);animation:lp 1.8s ease-in-out infinite;}
.led-x{background:radial-gradient(circle at 35% 30%,#3a2808,#1e1004);box-shadow:inset 0 1px 2px rgba(0,0,0,.7);}
@keyframes lp{0%,100%{filter:brightness(1);}50%{filter:brightness(1.4);}}
.badge{font-size:9px;letter-spacing:1px;padding:2px 8px;border-radius:3px;text-transform:uppercase;background:rgba(60,40,8,.9);color:var(--g1);border:1px solid var(--g4);}

/* EQ */
.eq-top{display:flex;justify-content:flex-end;margin-bottom:16px;}

/* VU METER */
.vu-panel{background:linear-gradient(180deg,#130a02 0%,#0e0602 100%);border:1.5px solid var(--g4);border-left:3px solid var(--g2);border-radius:6px;padding:10px 14px 8px;margin-bottom:16px;}
.vu-hdr{font-family:var(--mono);font-size:9px;letter-spacing:3px;text-transform:uppercase;color:var(--g3);margin-bottom:8px;}
.vu-row{display:flex;align-items:center;gap:8px;margin-bottom:5px;}
.vu-ch{font-family:var(--mono);font-size:10px;font-weight:700;letter-spacing:1px;color:var(--tx3);width:12px;flex-shrink:0;}
.vu-bar{display:flex;gap:2px;flex:1;height:14px;}
.vs{flex:1;border-radius:1px;}
.vs.on.z-a{background:#748530;box-shadow:0 0 4px rgba(116,133,48,.9),inset 0 1px 0 rgba(180,210,80,.3);}
.vs.off.z-a{background:#0e1205;border:1px solid #1c240a;}
.vs.on.z-y{background:#9c590e;box-shadow:0 0 5px rgba(156,89,14,.9),inset 0 1px 0 rgba(220,150,60,.3);}
.vs.off.z-y{background:#140a02;border:1px solid #241404;}
.vs.on.z-r{background:#9c0e0e;box-shadow:0 0 7px rgba(156,14,14,.9),inset 0 1px 0 rgba(220,60,60,.3);}
.vs.off.z-r{background:#140202;border:1px solid #240404;}
.vs.pk.z-a{background:#b8d050;box-shadow:0 0 8px rgba(160,190,50,1),inset 0 1px 0 rgba(210,240,120,.5);}
.vs.pk.z-y{background:#e07820;box-shadow:0 0 10px rgba(200,100,20,1),inset 0 1px 0 rgba(240,180,80,.5);}
.vs.pk.z-r{background:#e02020;box-shadow:0 0 12px rgba(200,20,20,1),inset 0 1px 0 rgba(240,80,80,.4);}
.vu-scale{position:relative;height:11px;margin:2px 20px 0;}
.vu-scale span{position:absolute;transform:translateX(-50%);font-family:var(--mono);font-size:7px;color:var(--tx3);}

.adv-sec{display:none;}.adv-sec.open{display:block;}
.pad-wrap{position:relative;display:flex;align-items:center;justify-content:center;margin:8px 0 18px;height:330px;}
.plbl{position:absolute;font-family:var(--mono);font-size:9px;letter-spacing:2px;text-transform:uppercase;
  color:rgba(200,160,60,.7);pointer-events:none;text-align:center;font-weight:700;}
.plbl.t{top:-10px;left:50%;transform:translateX(-50%);}
.plbl.b{bottom:-10px;left:50%;transform:translateX(-50%);}
.plbl.l{left:14px;top:50%;transform:translateY(-50%);}
.plbl.r{right:14px;top:50%;transform:translateY(-50%);}
#pad{border-radius:50%;cursor:crosshair;touch-action:none;display:block;
  box-shadow:0 0 0 3px var(--g5),0 0 0 7px var(--g4),0 0 0 10px var(--g3),0 0 0 13px var(--g2),0 0 0 15px var(--g1),0 0 0 17px var(--g3),0 0 0 19px var(--g5),0 0 0 21px rgba(0,0,0,.4),0 8px 40px rgba(0,0,0,.9);}
#puck{position:absolute;width:44px;height:44px;border-radius:50%;left:50%;top:50%;
  background:radial-gradient(circle at 30% 25%,var(--g-sh) 0%,var(--g1) 18%,var(--g2) 40%,var(--g3) 62%,var(--g4) 80%,var(--g5) 100%);
  box-shadow:inset 0 3px 4px rgba(255,230,140,.55),inset 0 -2px 4px rgba(0,0,0,.6),0 0 0 3px var(--g5),0 0 28px var(--am),0 0 55px rgba(255,144,32,.3);
  transform:translate(-50%,-50%);pointer-events:none;}
#puck::after{content:'';position:absolute;inset:4px;border-radius:50%;border:2px solid rgba(255,200,80,.25);}
.gains{display:flex;gap:6px;justify-content:space-between;margin-bottom:16px;}
.gcol{flex:1;text-align:center;border-radius:5px;padding:8px 3px;background:linear-gradient(180deg,#1a0e02 0%,#140a00 100%);border:1.5px solid var(--g4);box-shadow:inset 0 2px 6px rgba(0,0,0,.6);}
.glbl{font-family:var(--mono);font-size:9px;letter-spacing:1px;text-transform:uppercase;color:var(--tx3);margin-bottom:5px;}
.gval{font-family:var(--mono);font-size:14px;font-weight:700;color:var(--g1);text-shadow:0 0 10px rgba(240,192,96,.5);}
.eq-card{background:linear-gradient(180deg,#2a1808 0%,#1e1004 100%);border:1.5px solid var(--g4);border-left:3px solid var(--g2);border-radius:6px;padding:14px 16px;margin-bottom:12px;overflow:visible;}
.eq-card h4{font-family:var(--mono);font-size:10px;letter-spacing:2.5px;text-transform:uppercase;color:var(--g2);margin-bottom:12px;}
.slr{display:flex;align-items:center;gap:10px;margin:10px 0;}
.sll{font-family:var(--mono);font-size:10px;letter-spacing:1px;text-transform:uppercase;color:var(--tx3);min-width:34px;}
.slv{font-family:var(--mono);font-size:11px;color:var(--g1);min-width:70px;text-align:right;}
input[type=range]{-webkit-appearance:none;flex:1;height:5px;cursor:pointer;background:linear-gradient(180deg,#0e0802 0%,#1e1406 50%,#0e0802 100%);border-radius:3px;outline:none;border:1px solid var(--g5);}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:20px;height:20px;border-radius:50%;cursor:pointer;background:radial-gradient(circle at 32% 28%,var(--g-sh) 0%,var(--g1) 25%,var(--g2) 55%,var(--g4) 85%,var(--g5) 100%);box-shadow:0 0 0 2px var(--g5),0 2px 6px rgba(0,0,0,.6);}

/* MEMORIAS */
.mbar{display:flex;gap:8px;margin-top:20px;justify-content:center;align-items:flex-start;overflow:visible;flex-wrap:wrap;}
.mem-led{width:8px;height:8px;border-radius:50%;background:radial-gradient(circle at 35% 30%,#2a1808,#0e0604);box-shadow:inset 0 1px 2px rgba(0,0,0,.8);transition:all .2s;flex-shrink:0;}
.mem-active .mem-led{background:radial-gradient(circle at 35% 30%,#ffe090,#e8a020)!important;box-shadow:0 0 6px rgba(232,160,32,1),0 0 12px rgba(232,160,32,.5)!important;animation:mled 2s ease-in-out infinite;}
.mem-stored .mem-led{background:radial-gradient(circle at 35% 30%,#a06010,#4a2806)!important;box-shadow:0 0 4px rgba(160,96,16,.5)!important;}
@keyframes mled{0%,100%{filter:brightness(1);}50%{filter:brightness(1.35);}}
.mem-active{color:var(--g-sh)!important;}
.mem-stored{color:var(--g3);}
.save-armed{animation:sarm .8s ease-in-out infinite;transform:translateY(4px);border-bottom-width:1px!important;box-shadow:0 1px 4px rgba(0,0,0,.5),0 0 20px rgba(255,200,80,.4)!important;}
.save-armed #save-led{animation:redpulse .5s ease-in-out infinite alternate;}
@keyframes sarm{0%,100%{box-shadow:0 1px 4px rgba(0,0,0,.5),0 0 15px rgba(255,200,80,.3);}50%{box-shadow:0 1px 4px rgba(0,0,0,.5),0 0 
  30px rgba(255,200,80,.6);}}
@keyframes redpulse{from{box-shadow:0 0 4px rgba(220,40,40,.7),0 0 8px rgba(220,40,40,.4);}to{box-shadow:0 0 10px rgba(255,60,60,1),0 0 20px rgba(255,60,60,.7);}}
.mem-pick{animation:mpick .7s ease-in-out infinite alternate;}
.mem-pick .mem-led{background:radial-gradient(circle at 35% 30%,#ffe090,#e8a020)!important;box-shadow:0 0 8px rgba(232,160,32,.9)!important;}
@keyframes mpick{from{opacity:.5;}to{opacity:1;}}

/* FORMS */
.sec-t{font-family:var(--mono);font-size:10px;font-weight:700;letter-spacing:3px;text-transform:uppercase;color:var(--g2);margin:22px 0 12px;padding-bottom:8px;border-bottom:1px solid var(--g4);}
.sec-t.fold{cursor:pointer;user-select:none;display:flex;justify-content:space-between;align-items:center;}
.sec-t.fold::after{content:'\25B2';font-size:8px;transition:transform .2s;}
.sec-t.fold.closed::after{transform:rotate(180deg);}
.sec-body{overflow:hidden;transition:max-height .3s ease,opacity .2s;max-height:2000px;opacity:1;}
.sec-body.closed{max-height:0;opacity:0;}
label{display:block;font-family:var(--mono);font-size:10px;letter-spacing:1.5px;text-transform:uppercase;color:var(--tx3);margin-top:12px;margin-bottom:4px;}
input[type=text],input[type=password],input[type=number]{width:100%;padding:9px 12px;background:linear-gradient(180deg,#120a02 0%,#1a1006 100%);border:1.5px solid var(--g4);border-radius:4px;font-family:var(--mono);font-size:13px;color:var(--tx);outline:none;box-shadow:inset 0 2px 6px rgba(0,0,0,.6);transition:border .15s;}
input:focus{border-color:var(--g2);}
.frow{display:flex;gap:10px;}.frow>div{flex:1;}
small{font-family:var(--mono);font-size:10px;color:var(--tx3);letter-spacing:.5px;line-height:1.7;}

/* TOAST */
#toast{position:fixed;bottom:24px;left:50%;transform:translateX(-50%);font-family:var(--mono);font-size:11px;letter-spacing:2px;text-transform:uppercase;padding:10px 22px;border-radius:4px;background:linear-gradient(180deg,#2e1c08 0%,#1e1004 100%);border:1.5px solid var(--g2);color:var(--am2);box-shadow:0 0 24px rgba(200,146,42,.25),0 6px 24px rgba(0,0,0,.8);visibility:hidden;opacity:0;transition:opacity .25s;z-index:999;pointer-events:none;white-space:nowrap;}
/* ═══ SLEEP OVERLAY ═══ */
body.sleeping .hdr,body.sleeping .face{filter:grayscale(1) brightness(0.5);transition:filter 1.5s ease;}
#sleep-overlay{display:none;position:fixed;top:0;left:0;right:0;bottom:0;z-index:9999;
  flex-direction:column;align-items:center;justify-content:center;
  background:rgba(0,0,0,0.65);backdrop-filter:blur(3px);}
.sleep-icon{font-size:64px;opacity:0.7;animation:sleepPulse 2s ease-in-out infinite;}
.sleep-msg{font-family:var(--mono);font-size:14px;color:#888;letter-spacing:3px;text-transform:uppercase;margin-top:12px;}
.sleep-sec{font-family:var(--mono);font-size:42px;font-weight:700;color:#606060;margin-top:8px;}
@keyframes sleepPulse{0%,100%{opacity:0.4;transform:scale(1);}50%{opacity:0.8;transform:scale(1.05);}}
</style></head><body>
<div id='sleep-overlay'><div class='sleep-icon'>&#x1F4A4;</div><div class='sleep-msg'>entrando en reposo</div><div class='sleep-sec'>90</div></div>
<div id='toast'></div>
<div class='hdr'>
  <div class='screw-row'><div class='screw'></div><div class='screw'></div></div>
  <div class='logo-area'>
    <div class='copper-plate'>DSP</div>
    <div><div class='logo-title'>Radiocassete</div><div class='logo-sub'>by robertocreaciones</div><div class='logo-ver' id='fw-ver'></div></div>
    <a onclick="toggleMute()" id='mute-btn' class='mute-btn'>&#x1F50A; ON</a>
    <div class='hdr-vu'>
      <div class='hdr-vu-col'><div class='hdr-vu-bar' id='vu-hdr-L'></div><span class='hdr-vu-ch'>L</span></div>
      <div class='hdr-vu-col'><div class='hdr-vu-bar' id='vu-hdr-R'></div><span class='hdr-vu-ch'>R</span></div>
    </div>
  </div>
  <nav>
    <a onclick="go('eq')"     id='n-eq' class='active'>EQ</a>
    <a onclick="go('adv')"    id='n-adv'>Advanced</a>
    <a onclick="go('status')" id='n-status'>Status</a>
    <a onclick="go('config')" id='n-config'>Config</a>
    <a onclick="go('update')" id='n-update'>Update</a>
  </nav>
</div>
<div class='face'>

<div class='page' id='p-status'>
  <div class='panel'>
    <div class='panel-title'>Estado del Sistema</div>
    <div class='sr'><span class='sl'>IP Address</span>  <span class='sv' id='sv-ip'>—</span></div>
    <div class='sr'><span class='sl'>Network</span>      <span class='sv' id='sv-net'>—</span></div>
    <div class='sr'><span class='sl'>Hostname</span>     <span class='sv hot' id='sv-ota-host'>—</span></div>
    <div class='sr'><span class='sl'>TCP Port</span>     <span class='sv'>8086</span></div>
    <div style='border-top:1px solid var(--g4);margin:8px 0 6px;'></div>
    <div class='sr'><span class='sl'>DSP</span>          <span class='sv' id='sv-dsp'><span class='led led-x'></span><span class='off'>—</span></span></div>
    <div class='sr'><span class='sl'>SigmaStudio</span>  <span class='sv'><span class='led led-x' id='tcp-led'></span><span class='off' id='tcp-t'>Desconectado</span></span></div>
    <div class='sr'><span class='sl'>Capture</span>      <span class='sv' id='sv-cap'><span class='led led-x'></span><span class='off'>Waiting Download</span></span></div>
  </div>

  <div class='sec-t fold' onclick='toggleSec(this)'>Control DSP</div>
  <div class='sec-body'>
    <div class='sr' style='margin-top:4px'><button class='pbtn pbtn-dark' id='dsplock-btn' onclick='toggleDspLock()'>&#x1F513;&ensp;DSP Lock</button><span class='sv'><span class='led led-x' id='dsplock-led'></span><span class='off' id='dsplock-t'>OFF</span></span></div>
    <div class='sr' style='margin-top:8px'><button class='pbtn pbtn-dark' id='eqboot-btn' onclick='toggleEqBoot()'>&#x23CF;&ensp;EQ Boot</button>  <span class='sv'><span class='led led-g' id='eqboot-led'></span><span class='on' id='eqboot-t'>ON</span></span></div>
    <div style='border-top:1px solid var(--g4);margin:10px 0 6px;'></div>
    <div class='sr'><button class='pbtn pbtn-dark' onclick='doReset()'>&#x21BA;&ensp;Reset DSP</button></div>
    <div class='sr' style='margin-top:8px;display:none' id='eeprom-row'>
      <button class='pbtn pbtn-brass' id='eeprom-btn' onclick='doEEPROM()'>&#x1F4BE;&ensp;Write EEPROM &mdash; Selfboot</button>
    </div>
    <div id='eeprom-warn' style='margin-top:8px;display:none'>
      <small>&#x26A0;&ensp;Haz primero <b>Link&rarr;Compile&rarr;Download</b> en SigmaStudio.</small>
    </div>
    <div class='sr' style='margin-top:8px'>
      <button class='pbtn pbtn-dark' onclick='doReadEEPROM()'>&#x1F4E5;&ensp;Read EEPROM &mdash; Backup</button>
    </div>
  </div>

  <div class='sec-t fold closed' onclick='toggleSec(this)'>Esquemas DSP (Bancos)</div>
  <div class='sec-body closed'>
  <small>Guarda el binario descargado y estas direcciones para alternar entre diferentes programaciones de SigmaStudio al vuelo.</small>
  <div style='margin-top:10px;'>
    <div class='frow' style='margin-bottom:4px'>
      <button class='pbtn pbtn-dark' id='btn-ram-s0' onclick='loadSchema(0, true)'>RAM B1</button>
      <button class='pbtn pbtn-dark' id='btn-ram-s1' onclick='loadSchema(1, true)'>RAM B2</button>
      <button class='pbtn pbtn-dark' id='btn-ram-s2' onclick='loadSchema(2, true)'>RAM B3</button>
      <button class='pbtn pbtn-dark' id='btn-ram-s3' onclick='loadSchema(3, true)'>RAM B4</button>
    </div>
    <div class='frow' style='margin-bottom:8px'>
      <button class='pbtn pbtn-dark' id='btn-epm-s0' onclick='loadSchema(0, false)'>EPM B1</button>
      <button class='pbtn pbtn-dark' id='btn-epm-s1' onclick='loadSchema(1, false)'>EPM B2</button>
      <button class='pbtn pbtn-dark' id='btn-epm-s2' onclick='loadSchema(2, false)'>EPM B3</button>
      <button class='pbtn pbtn-dark' id='btn-epm-s3' onclick='loadSchema(3, false)'>EPM B4</button>
    </div>
    <div class='frow' id='schema-save-row' style='display:none;'>
      <button class='pbtn pbtn-brass' style='font-size:8px;padding:6px' onclick='saveSchema(0)'>Save B1</button>
      <button class='pbtn pbtn-brass' style='font-size:8px;padding:6px' onclick='saveSchema(1)'>Save B2</button>
      <button class='pbtn pbtn-brass' style='font-size:8px;padding:6px' onclick='saveSchema(2)'>Save B3</button>
      <button class='pbtn pbtn-brass' style='font-size:8px;padding:6px' onclick='saveSchema(3)'>Save B4</button>
    </div>
    <div style='border-top:1px solid var(--g4);margin:10px 0 6px;'></div>
    <small>Descargar / Importar bancos como archivo:</small>
    <div class='frow' style='margin-top:6px;margin-bottom:4px'>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' id='btn-dl-s0' onclick='dlSchema(0)'>&#x2B07; B1</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' id='btn-dl-s1' onclick='dlSchema(1)'>&#x2B07; B2</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' id='btn-dl-s2' onclick='dlSchema(2)'>&#x2B07; B3</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' id='btn-dl-s3' onclick='dlSchema(3)'>&#x2B07; B4</button>
    </div>
    <div class='frow' style='margin-bottom:4px'>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' onclick='ulSchema(0)'>&#x2B06; B1</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' onclick='ulSchema(1)'>&#x2B06; B2</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' onclick='ulSchema(2)'>&#x2B06; B3</button>
      <button class='pbtn pbtn-dark' style='font-size:8px;padding:6px' onclick='ulSchema(3)'>&#x2B06; B4</button>
    </div>
    <input type='file' id='schema-file-input' accept='.rcbin' style='display:none'>
    <div id='schema-active-info' style='margin-top:8px;font-size:10px;letter-spacing:1px;color:var(--tx2);text-align:center;'></div>
  </div>
  </div>
</div>

<div class='page active' id='p-eq'>
  <div class='vu-panel'>
    <div class='vu-hdr'>VU Meter</div>
    <div class='vu-row'><span class='vu-ch'>L</span><div class='vu-bar' id='vu-L'></div></div>
    <div class='vu-row'><span class='vu-ch'>R</span><div class='vu-bar' id='vu-R'></div></div>
    <div class='vu-scale'>
      <span style='left:2.5%'>-40</span><span style='left:17.5%'>-20</span>
      <span style='left:37.5%'>-10</span><span style='left:52.5%'>-6</span>
      <span style='left:67.5%'>-3</span><span style='left:92.5%'>0</span>
    </div>
  </div>
  <div class='pad-wrap'>
    <span class='plbl t'>Brillante</span><span class='plbl b'>C&aacute;lido</span>
    <span class='plbl l'>Relajado</span><span class='plbl r'>Energ&eacute;tico</span>
    <div style='position:relative;display:inline-block;line-height:0'>
      <canvas id='pad' width='252' height='252'></canvas>
      <div id='puck'></div>
    </div>
  </div>

  <div class='eq-card' style='margin-bottom:16px;padding:12px;'>
    <div class='slr'>
      <span style='color:var(--am2);font-size:11px;font-weight:600;min-width:72px;'>Bass Freq</span>
      <input type='range' id='sl-bf' min='20' max='90' value='60' oninput='onBass()'>
      <span class='slv' id='vl-bf' style='min-width:46px;'>60 Hz</span>
    </div>
    <div class='slr' style='margin-top:8px;'>
      <span style='color:var(--am2);font-size:11px;font-weight:600;min-width:72px;'>Boost</span>
      <input type='range' id='sl-bb' min='0' max='16' step='0.5' value='0' oninput='onBass()'>
      <span class='slv' id='vl-bb' style='min-width:46px;'>0.0 dB</span>
    </div>
    <div class='slr' style='margin-top:8px;'>
      <span style='color:var(--am2);font-size:11px;font-weight:600;min-width:72px;'>Comp Ratio</span>
      <input type='range' id='sl-bc' min='1' max='20' step='0.5' value='10' oninput='onBass()'>
      <span class='slv' id='vl-bc' style='min-width:46px;'>10.0 : 1</span>
    </div>
  </div>

  <div class='gains'>
    <div class='gcol' onclick='goBand(0)' style='cursor:pointer'><div class='glbl' id='gf0'>—</div><div class='gval' id='gv0'>0.0</div></div>
    <div class='gcol' onclick='goBand(1)' style='cursor:pointer'><div class='glbl' id='gf1'>—</div><div class='gval' id='gv1'>0.0</div></div>
    <div class='gcol' onclick='goBand(2)' style='cursor:pointer'><div class='glbl' id='gf2'>—</div><div class='gval' id='gv2'>0.0</div></div>
    <div class='gcol' onclick='goBand(3)' style='cursor:pointer'><div class='glbl' id='gf3'>—</div><div class='gval' id='gv3'>0.0</div></div>
    <div class='gcol' onclick='goBand(4)' style='cursor:pointer'><div class='glbl' id='gf4'>—</div><div class='gval' id='gv4'>0.0</div></div>
    <div class='gcol' onclick='goBand(5)' style='cursor:pointer'><div class='glbl' id='gf5'>—</div><div class='gval' id='gv5'>0.0</div></div>
    <div class='gcol' onclick='goBand(6)' style='cursor:pointer'><div class='glbl' id='gf6'>—</div><div class='gval' id='gv6'>0.0</div></div>
    <div class='gcol' onclick='goBand(7)' style='cursor:pointer'><div class='glbl' id='gf7'>—</div><div class='gval' id='gv7'>0.0</div></div>
  </div>
  <div class='mbar'>
    <button class='pbtn pbtn-brass' onclick='memSave()' id='savebtn'>
      <span id='save-led' style='width:8px;height:8px;border-radius:50%;background:radial-gradient(circle at 35% 30%,#ff8080,#cc2020);box-shadow:0 0 6px rgba(220,40,40,.9),0 0 12px rgba(220,40,40,.5);flex-shrink:0;display:inline-block;'></span>
   
      Save
    </button>
    <button class='pbtn pbtn-dark' id='mb0' onclick='memPress(0)'><div class='mem-led'></div>M1</button>
    <button class='pbtn pbtn-dark' id='mb1' onclick='memPress(1)'><div class='mem-led'></div>M2</button>
    <button class='pbtn pbtn-dark' id='mb2' onclick='memPress(2)'><div class='mem-led'></div>M3</button>
    <button class='pbtn pbtn-dark' id='mb3' onclick='memPress(3)'><div class='mem-led'></div>M4</button>
    <button class='pbtn pbtn-dark' id='mb4' onclick='memPress(4)'><div class='mem-led'></div>M5</button>
    <button class='pbtn pbtn-dark' onclick='resetEq()'><div class='mem-led' style='visibility:hidden'></div>Rst</button>
  </div>
</div>

<div class='page' id='p-adv'>
  <div class='sec-t fold closed' onclick='toggleSec(this)'>Bandas EQ</div>
  <div class='sec-body closed'>
  <div class='eq-card' id='eqcard0'><h4>Band 1 &mdash; Low Shelf 40 Hz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f0' min='20' max='120' value='40' oninput='onSl(0,"f",this)'><span class='slv' id='fv0'>40 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g0' min='-12' max='12' step='0.5' value='0' oninput='onSl(0,"g",this)'><span class='slv' id='gvs0'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q0' min='0.1' max='4' step='0.1' value='0.7' oninput='onSl(0,"q",this)'><span class='slv' id='qv0'>0.70</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(0)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard1'><h4>Band 2 &mdash; Bell 100 Hz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f1' min='50' max='300' value='100' oninput='onSl(1,"f",this)'><span class='slv' id='fv1'>100 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g1' min='-12' max='12' step='0.5' value='0' oninput='onSl(1,"g",this)'><span class='slv' id='gvs1'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q1' min='0.1' max='10' step='0.1' value='1.0' oninput='onSl(1,"q",this)'><span class='slv' id='qv1'>1.00</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(1)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard2'><h4>Band 3 &mdash; Bell 250 Hz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f2' min='100' max='600' value='250' oninput='onSl(2,"f",this)'><span class='slv' id='fv2'>250 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g2' min='-12' max='12' step='0.5' value='0' oninput='onSl(2,"g",this)'><span class='slv' id='gvs2'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q2' min='0.1' max='10' step='0.1' value='1.2' oninput='onSl(2,"q",this)'><span class='slv' id='qv2'>1.20</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(2)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard3'><h4>Band 4 &mdash; Bell 800 Hz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f3' min='300' max='2000' value='800' oninput='onSl(3,"f",this)'><span class='slv' id='fv3'>800 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g3' min='-12' max='12' step='0.5' value='0' oninput='onSl(3,"g",this)'><span class='slv' id='gvs3'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q3' min='0.1' max='10' step='0.1' value='1.4' oninput='onSl(3,"q",this)'><span class='slv' id='qv3'>1.40</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(3)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard4'><h4>Band 5 &mdash; Bell 2.5 kHz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f4' min='800' max='5000' value='2500' oninput='onSl(4,"f",this)'><span class='slv' id='fv4'>2500 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g4' min='-12' max='12' step='0.5' value='0' oninput='onSl(4,"g",this)'><span class='slv' id='gvs4'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q4' min='0.1' max='10' step='0.1' value='1.4' oninput='onSl(4,"q",this)'><span class='slv' id='qv4'>1.40</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(4)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard5'><h4>Band 6 &mdash; Bell 5.0 kHz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f5' min='2000' max='10000' value='5000' oninput='onSl(5,"f",this)'><span class='slv' id='fv5'>5000 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g5' min='-12' max='12' step='0.5' value='0' oninput='onSl(5,"g",this)'><span class='slv' id='gvs5'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q5' min='0.1' max='10' step='0.1' value='1.2' oninput='onSl(5,"q",this)'><span class='slv' id='qv5'>1.20</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(5)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard6'><h4>Band 7 &mdash; Bell 10 kHz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f6' min='5000' max='18000' value='10000' oninput='onSl(6,"f",this)'><span class='slv' id='fv6'>10000 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g6' min='-12' max='12' step='0.5' value='0' oninput='onSl(6,"g",this)'><span class='slv' id='gvs6'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q6' min='0.1' max='10' step='0.1' value='1.0' oninput='onSl(6,"q",this)'><span class='slv' id='qv6'>1.00</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(6)'>&#x25A0;&ensp;Flat 0 dB</button></div>
  <div class='eq-card' id='eqcard7'><h4>Band 8 &mdash; High Shelf 16 kHz</h4>
    <div class='slr'><span class='sll'>Freq</span><input type='range' id='f7' min='8000' max='20000' value='16000' oninput='onSl(7,"f",this)'><span class='slv' id='fv7'>16000 Hz</span></div>
    <div class='slr'><span class='sll'>Gain</span><input type='range' id='g7' min='-12' max='12' step='0.5' value='0' oninput='onSl(7,"g",this)'><span class='slv' id='gvs7'>0.0 dB</span></div>
    <div class='slr'><span class='sll'>Q</span><input type='range' id='q7' min='0.1' max='4' step='0.1' value='0.7' oninput='onSl(7,"q",this)'><span class='slv' id='qv7'>0.70</span></div>
    <button class='pbtn pbtn-dark pbtn-full' onclick='flatBand(7)'>&#x25A0;&ensp;Flat 0 dB</button></div>

  </div>
  <div style='border-top:1.5px solid var(--g4);margin:16px 0 4px;'></div>
  <div class='sec-t fold closed' onclick='toggleSec(this)' style='margin-top:8px;'>Input Volume</div>
  <div class='sec-body closed'>
  <div class='eq-card'>
    <h4>BT Input &mdash; 0x0002</h4>
    <div class='slr'>
      <span class='sll'>Vol</span>
      <input type='range' id='ivol-bt' min='-30' max='6' step='0.5' value='0' oninput='onInputVol("bt",this)'>
      <span class='slv' id='ivol-bt-v'>0.0 dB</span>
    </div>
  </div>
  <div class='eq-card'>
    <h4>Line In &mdash; 0x0001 <button class='pbtn pbtn-dark' id='line-mute-btn' onclick='toggleLineMute()' style='float:right;padding:4px 10px;font-size:9px;min-width:auto;'>&#x1F50A; ON</button></h4>
    <div class='slr'>
      <span class='sll'>Vol</span>
      <input type='range' id='ivol-li' min='-30' max='6' step='0.5' value='0' oninput='onInputVol("li",this)'>
      <span class='slv' id='ivol-li-v'>0.0 dB</span>
    </div>
  </div>
  <div class='eq-card'>
    <h4>Sine Tone &mdash; 0x0009</h4>
    <div class='slr'>
      <span class='sll'>Vol</span>
      <input type='range' id='ivol-st' min='-30' max='6' step='0.5' value='0' oninput='onInputVol("st",this)'>
      <span class='slv' id='ivol-st-v'>0.0 dB</span>
    </div>
  </div>

  </div>
  <div style='border-top:1.5px solid var(--g4);margin:20px 0 12px;'></div>
  <div class='vu-panel'>
    <div class='vu-hdr'>VU Meter</div>
    <div class='vu-row'><span class='vu-ch'>L</span><div class='vu-bar' id='vu-L2'></div></div>
    <div class='vu-row'><span class='vu-ch'>R</span><div class='vu-bar' id='vu-R2'></div></div>
    <div class='vu-scale'>
      <span style='left:2.5%'>-40</span>
      <span style='left:17.5%'>-20</span>
      <span style='left:37.5%'>-10</span>
      <span style='left:52.5%'>-6</span>
      <span style='left:67.5%'>-3</span>
      <span style='left:92.5%'>0</span>
    </div>
    <div class='slr' style='margin-top:10px;margin-bottom:0;'>
      <span class='sll'>Gain</span>
      <input type='range' id='vu-gain-sl' min='0' max='20' step='0.5' value='0' oninput='onVuGain(this)'>
      <span class='slv' id='vu-gain-v' style='min-width:50px;'>+0.0 dB</span>
    </div>
  </div>
</div>

<div class='page' id='p-config'>
  <div class='sec-t fold closed' onclick='toggleSec(this)'>WiFi STA</div>
  <div class='sec-body closed'>
  <label>SSID</label><input type='text' id='cfg-ssid'>
  <label>Password</label><input type='password' id='cfg-pass' placeholder='dejar vac&iacute;o para mantener actual'>
  <button class='pbtn pbtn-dark pbtn-full' onclick='saveWifi()'>Save WiFi &amp; Reboot</button>
  </div>

  <div class='sec-t fold closed' onclick='toggleSec(this)'>Red &amp; Dispositivo</div>
  <div class='sec-body closed'>
  <small>Hostname, AP, OTA y puerto TCP. Requieren reinicio.</small>
  <label>Hostname</label><input type='text' id='cfg-hostname' placeholder='radiocassete'>
  <label>AP SSID</label><input type='text' id='cfg-ap-ssid' placeholder='Radiocassete'>
  <label>AP Password</label><input type='password' id='cfg-ap-pass' placeholder='dejar vac&iacute;o para mantener actual'>
  <label>OTA Password</label><input type='password' id='cfg-ota-pass' placeholder='vac&iacute;o = sin contrase&ntilde;a'>
  <label>TCP Port (SigmaStudio)</label><input type='number' id='cfg-tcp-port' min='1' max='65535' placeholder='8086'>
  <button class='pbtn pbtn-dark pbtn-full' onclick='saveNetwork()'>Save Red &amp; Reboot</button>
  </div>

  <div class='sec-t fold closed' onclick='toggleSec(this)'>GPIO Pins</div>
  <div class='sec-body closed'>
  <small>No usar GPIO 6&ndash;11 (flash).</small>
  <div class='frow'>
    <div><label>SCL</label><input type='number' id='cfg-scl'></div>
    <div><label>SDA</label><input type='number' id='cfg-sda'></div>
  </div>
  <div class='frow'>
    <div><label>Reset</label><input type='number' id='cfg-rst'></div>
    <div><label>Selfboot</label><input type='number' id='cfg-sb'></div>
  </div>
  <label>LED</label><input type='number' id='cfg-led'>
  <button class='pbtn pbtn-dark pbtn-full' onclick='savePins()'>Save Pins &amp; Reboot</button>
  </div>

  <div class='sec-t fold closed' onclick='toggleSec(this)'>DSP &amp; Direcciones Param RAM</div>
  <div class='sec-body closed'>
  <div style='margin-bottom:12px;padding:10px;background:rgba(0,0,0,.3);border:1px dashed var(--g4);border-radius:6px;text-align:center;'>
    <small style='display:block;margin-bottom:8px;'>Carga el archivo <b>_PARAM.h</b> de SigmaStudio para rellenar autom&aacute;ticamente todas las direcciones.</small>
    <input type='file' id='paramFileInput' accept='.h,.txt,.c' style='display:none'>
    <button class='pbtn pbtn-dark' onclick='document.getElementById("paramFileInput").click()'>&#x1F4C2;&ensp;Cargar _PARAM.h</button>
    <span id='paramFileName' style='display:block;margin-top:6px;font-size:10px;color:var(--tx3);'></span>
  </div>
  <small>Direcci&oacute;n I2C seg&uacute;n pines ADDR0/ADDR1: 0x34&ndash;0x37.</small>
  <label>ADAU1701 I2C Address</label><input type='text' id='cfg-dsp-addr' placeholder='0x34'>
  <div style='border-top:1px solid var(--g4);margin:12px 0 8px;'></div>
  <small>Acepta decimal (378) o hexadecimal (0x017A). Actualiza si cambias el esquema en SigmaStudio.</small>
  <label>Band 1</label><input type='text' id='cfg-a0' placeholder='0x017A'>
  <label>Band 2</label><input type='text' id='cfg-a1' placeholder='0x017F'>
  <label>Band 3</label><input type='text' id='cfg-a2' placeholder='0x0184'>
  <label>Band 4</label><input type='text' id='cfg-a3' placeholder='0x0189'>
  <label>Band 5</label><input type='text' id='cfg-a4' placeholder='0x018E'>
  <label>Band 6</label><input type='text' id='cfg-a5' placeholder='0x0193'>
  <label>Band 7</label><input type='text' id='cfg-a6' placeholder='0x0198'>
  <label>Band 8</label><input type='text' id='cfg-a7' placeholder='0x019D'>
  <div style='border-top:1px solid var(--g4);margin:12px 0 8px;'></div>
  <label>Bass Freq</label><input type='text' id='cfg-bfa' placeholder='0x0011'>
  <label>Bass Boost</label><input type='text' id='cfg-bba' placeholder='0x0017'>
  <label>Bass Comp Ratio</label><input type='text' id='cfg-bca' placeholder='0x0010'>
  <div style='border-top:1px solid var(--g4);margin:12px 0 8px;'></div>
  <label>BT Input Vol addr</label><input type='text' id='cfg-ivbt' placeholder='0x0002'>
  <label>Line In Vol addr</label><input type='text' id='cfg-ivli' placeholder='0x0001'>
  <label>Sine Tone Vol addr</label><input type='text' id='cfg-ivst' placeholder='0x0009'>
  <div style='border-top:1px solid var(--g4);margin:12px 0 8px;'></div>
  <label>VU L Peak addr</label><input type='text' id='cfg-vul' placeholder='0x0200'>
  <label>VU R Peak addr</label><input type='text' id='cfg-vur' placeholder='0x0201'>
  <label>VU Window (ms)</label><input type='number' id='cfg-vu-win' min='50' max='2000' placeholder='250'>
  <div style='border-top:1px solid var(--g4);margin:12px 0 8px;'></div>
  <small>Sine Tone L/R &mdash; Direcciones del m&oacute;dulo Tone (Lookup) de SigmaStudio.</small>
  <label>Tone L &mdash; Mask</label><input type='text' id='cfg-stlm' placeholder='0x0004'>
  <label>Tone L &mdash; Increment</label><input type='text' id='cfg-stli' placeholder='0x0005'>
  <label>Tone L &mdash; IsOn</label><input type='text' id='cfg-stlo' placeholder='0x0006'>
  <label>Tone R &mdash; Mask</label><input type='text' id='cfg-strm' placeholder='0x0000'>
  <label>Tone R &mdash; Increment</label><input type='text' id='cfg-stri' placeholder='0x0001'>
  <label>Tone R &mdash; IsOn</label><input type='text' id='cfg-stro' placeholder='0x0002'>
  <button class='pbtn pbtn-brass pbtn-full' onclick='saveAddrs()'>Save DSP &amp; Addresses</button>
  </div>
</div>

<div class='page' id='p-update'>
  <div class='panel'>
    <div class='panel-title'>Firmware OTA</div>
    <div class='sr'><span class='sl'>Firmware</span><span class='sv hot' id='sv-fw-ver2'>—</span></div>
    <div class='sr'><span class='sl'>OTA Hostname</span><span class='sv' id='sv-ota-host2'>—</span></div>
    <div class='sr'><span class='sl'>OTA Puerto</span>   <span class='sv'>3232</span></div>
    <div class='sr'><span class='sl'>OTA Password</span> <span class='sv'>adau1701ota</span></div>
    <div style='margin:8px 0'>
      <small>Arduino IDE: <b>Tools &rarr; Port &rarr; hostname.local</b> y haz Upload normalmente.<br>
      O sube un <b>.bin</b> aqu&iacute;:</small>
    </div>
    <label>Archivo .bin</label>
    <input type='file' id='bin-file' accept='.bin'
      style='width:100%;padding:9px 12px;background:linear-gradient(180deg,#120a02,#1a1006);
  border:1.5px solid var(--g4);border-radius:4px;font-family:var(--mono);
      font-size:12px;color:var(--tx);margin-bottom:12px;'>
    <div id='ota-bar-wrap' style='display:none;margin-bottom:12px;height:8px;
  background:#1a1006;border-radius:4px;border:1px solid var(--g4);overflow:hidden;'>
      <div id='ota-bar' style='height:100%;width:0%;
        background:linear-gradient(90deg,var(--g3),var(--g1));
  border-radius:4px;transition:width .3s;'></div>
    </div>
    <div id='ota-status' style='font-family:var(--mono);font-size:11px;
  color:var(--tx3);margin-bottom:12px;min-height:16px;letter-spacing:1px;'></div>
    <button class='pbtn pbtn-brass pbtn-full' onclick='doHttpOta()'>
      &#x2191;&ensp;Upload Firmware
    </button>
  </div>

  <div class='panel'>
    <div class='panel-title'>Backup &amp; Restore</div>
    <small>Descarga un archivo con toda la configuraci&oacute;n, presets EQ y esquemas DSP. En caso de fallo total, restaura todo al estado del backup.</small>
    <div class='frow' style='margin-top:12px'>
      <button class='pbtn pbtn-brass' onclick='doBackup()'>&#x1F4E6;&ensp;Full Backup</button>
      <button class='pbtn pbtn-dark' onclick='doRestore()'>&#x1F4E5;&ensp;Restore Backup</button>
    </div>
    <input type='file' id='restore-file-input' accept='.rcbak' style='display:none'>
  </div>

  <div class='panel'>
    <div class='panel-title'>Consola Log</div>
    <div style='display:flex;gap:8px;margin-bottom:10px;align-items:center;justify-content:space-between;'>
      <button class='pbtn pbtn-dark' style='padding:5px 12px;min-width:0;font-size:10px;' id='log-btn' onclick='toggleLog()'><span class='led led-x' id='log-led' style='margin-right:4px'></span><span id='log-t'>OFF</span></button>
      <label style='margin:0;display:flex;align-items:center;gap:6px;cursor:pointer;'>
        <input type='checkbox' id='log-auto' checked onchange='toggleLogAuto()'> Auto-refresh
      </label>
      <button class='pbtn pbtn-dark' style='padding:5px 12px;min-width:0;font-size:10px;'
  onclick='clearLogDisplay()'>Clear</button>
    </div>
    <div id='log-console' style='
      font-family:var(--mono);font-size:10px;line-height:1.6;
      color:#90c890;background:#0a0600;border:1.5px solid var(--g5);
  border-radius:4px;padding:10px;height:220px;overflow-y:auto;
      white-space:pre-wrap;word-break:break-all;
      box-shadow:inset 0 2px 8px rgba(0,0,0,.8);'></div>
  </div>

  <div class='sec-t fold closed' onclick='toggleSec(this)'>Zona Peligrosa</div>
  <div class='sec-body closed'>
  <div class='sr'><button class='pbtn pbtn-red' onclick='rebootESP()'>&#x26A0;&ensp;Reset ESP32</button></div>
  <div class='sr' style='margin-top:10px'><button class='pbtn pbtn-red pbtn-full' onclick='clearPresets()'>&#x2715;&ensp;Clear All Presets</button></div>
  <div class='sr' style='margin-top:10px'><button class='pbtn pbtn-red pbtn-full' onclick='factoryReset()'>&#x2715;&ensp;Factory Reset</button></div>
  <div style='margin-top:8px'><small>Factory Reset borra toda la configuraci&oacute;n NVS, presets y esquemas. El ESP32 reinicia en AP mode.</small></div>
  </div>
</div>

</div><script>
// ── VU Meter ─────────────────────────────────────────────────
var VU_THRESH=[-40,-34,-28,-22,-18,-14,-12,-10,-8,-7,-6,-5,-4,-3,-2,-1.5,-1,-0.5,0,3].map(function(d){return Math.pow(10,d/20);});
var VU_ZONE  =['a','a','a','a','a','a','a','a','a','a','y','y','y','y','r','r','r','r','r','r'];
var vuTimer=null;
var VU_PEAK_HOLD=350;     // ms máximo que un LED pico puede estar encima de la barra
var VU_IDS=['vu-L','vu-R','vu-L2','vu-R2'];
var vuPeak={};
VU_IDS.forEach(function(id){vuPeak[id]={idx:-1,ts:0};});
var vuTargetL=0,vuTargetR=0,vuCurrL=0,vuCurrR=0,vuRafRunning=false;
var VU_ATK=1.0, VU_REL=0.20;    // ataque instantáneo / caída más agradable visualmente
var vuLastSseMs=0;               // timestamp del último SSE recibido

// ── Mini VU del header (6 segmentos, φ-proportioned) ──────────
var HDR_VU_N=6;
var HDR_VU_THRESH=[-36,-14,-6,-1,0,3].map(function(d){return Math.pow(10,d/20);});
var HDR_VU_ZONE=['a','a','a','y','r','r'];
var HDR_VU_IDS=['vu-hdr-L','vu-hdr-R'];
function initHdrVU(){
  HDR_VU_IDS.forEach(function(id){
    var b=document.getElementById(id); if(!b)return;
    b.innerHTML='';
    for(var i=0;i<HDR_VU_N;i++){var s=document.createElement('span');s.className='vs z-'+HDR_VU_ZONE[i]+' off';b.appendChild(s);}
  });
}
function setHdrVU(id,lin){
  var b=document.getElementById(id); if(!b)return;
  var c=b.children;
  for(var i=0;i<HDR_VU_N;i++){
    c[i].className='vs z-'+HDR_VU_ZONE[i]+(lin>=HDR_VU_THRESH[i]?' on':' off');
  }
}

function initVUBars(){
  VU_IDS.forEach(function(id){
    var b=document.getElementById(id); if(!b)return;
    b.innerHTML='';
    for(var i=0;i<20;i++){var s=document.createElement('span');s.className='vs z-'+VU_ZONE[i]+' off';b.appendChild(s);}
    vuPeak[id]={idx:-1,ts:0};
  });
  initHdrVU();
}
function setVUBar(id,lin){
  var b=document.getElementById(id); if(!b)return;
  var c=b.children;
  var now=Date.now();
  var cur=-1;
  for(var i=19;i>=0;i--){ if(lin>=VU_THRESH[i]){cur=i;break;} }
  var pk=vuPeak[id];
  if(cur>=pk.idx){
    // Señal sube o igual — actualizar pico inmediatamente
    pk.idx=cur; pk.ts=now;
  } else if(now-pk.ts>VU_PEAK_HOLD){
    // Hold expirado (50 ms) — snap instantáneo al nivel actual
    pk.idx=cur; pk.ts=now;
  }
  for(var i=0;i<20;i++){
    var on=lin>=VU_THRESH[i];
    var isPeak=(i===pk.idx && pk.idx>=0);
    c[i].className='vs z-'+VU_ZONE[i]+(on||isPeak?' on':' off')+(isPeak?' pk':'');
  }
}
function pollVU(){}  // VU llega por SSE
function vuRafTick(){
  if(!vuRafRunning) return;
  if(Date.now()-vuLastSseMs>500){vuTargetL=0;vuTargetR=0;}  // SSE timeout → apagar
  var dL=vuTargetL-vuCurrL, dR=vuTargetR-vuCurrR;
  vuCurrL+=dL*(dL>=0?VU_ATK:VU_REL);
  vuCurrR+=dR*(dR>=0?VU_ATK:VU_REL);
  var l=Math.min(vuCurrL*vuDispGain,2.0);
  var r=Math.min(vuCurrR*vuDispGain,2.0);
  setVUBar('vu-L',l); setVUBar('vu-R',r);
  setVUBar('vu-L2',l); setVUBar('vu-R2',r);
  setHdrVU('vu-hdr-L',l); setHdrVU('vu-hdr-R',r);
  requestAnimationFrame(vuRafTick);
}
function startVU(){
  initVUBars();
  vuTargetL=0; vuTargetR=0; vuCurrL=0; vuCurrR=0;
  if(!vuRafRunning){vuRafRunning=true; requestAnimationFrame(vuRafTick);}
}
function stopVU(){
  vuRafRunning=false;
  vuTargetL=0; vuTargetR=0; vuCurrL=0; vuCurrR=0;
  VU_IDS.forEach(function(id){vuPeak[id]={idx:-1,ts:0}; setVUBar(id,0);});
}

var vuDispGain=1.0;
function onVuGain(el){
  var db=parseFloat(el.value);
  vuDispGain=Math.pow(10,db/20);
  document.getElementById('vu-gain-v').textContent='+'+db.toFixed(1)+' dB';
}

function go(n){
  document.querySelectorAll('.page').forEach(p=>p.classList.remove('active'));
  document.querySelectorAll('nav a').forEach(a=>a.classList.remove('active'));
  document.getElementById('p-'+n).classList.add('active');
  document.getElementById('n-'+n).classList.add('active');
  localStorage.setItem('activeTab',n);
  if(n==='status') { refreshStatus(); refreshSchemasUI(); }
  if(n==='eq')     { refreshEQ(); setTimeout(initPad,60); }
  if(n==='adv')    refreshEQ();
  if(n==='config') refreshConfig();
  if(n==='update') fetchLog();
}


function toast(msg){
  var el=document.getElementById('toast');
  el.textContent=msg;el.style.visibility='visible';el.style.opacity='1';
  clearTimeout(el._t);
  el._t=setTimeout(()=>{el.style.opacity='0';setTimeout(()=>el.style.visibility='hidden',260);},2400);
  }

var logOn=false, capReady=false;
function refreshStatus(){
  fetch('/status').then(r=>r.json()).then(d=>{ capReady=d.captureReady; applyStatus(d); }).catch(()=>{});
}
function doReset(){ fetch('/reset_dsp',{method:'POST'}).then(()=>{toast('DSP Reset OK');refreshStatus();}); }

function rebootESP(){
  if(confirm('¿Reiniciar el ESP32? Se perderá la conexión temporalmente.')){
    fetch('/reboot_esp', {method:'POST'}).then(() => toast('Reiniciando ESP32...'));
  }
}

function toggleLog(){ fetch('/toggle_log',{method:'POST'}).then(()=>refreshStatus());
  }
function toggleEqBoot(){ fetch('/toggle_eq_boot',{method:'POST'}).then(()=>refreshStatus()); }
function toggleDspLock(){ fetch('/toggle_dsp_lock',{method:'POST'}).then(()=>refreshStatus()); }
function toggleMute(){ fetch('/toggle_mute',{method:'POST'}).then(()=>refreshStatus()); }
function toggleLineMute(){ fetch('/toggle_line_mute',{method:'POST'}).then(()=>refreshStatus()); }
function doEEPROM(){
  if(!capReady){toast('No hay captura disponible');return;}
  toast('Escribiendo EEPROM...');
  fetch('/save_eeprom',{method:'POST'}).then(r=>r.text()).then(t=>toast('EEPROM: '+t));
}
function doReadEEPROM(){
  toast('Leyendo EEPROM por I2C...');
  fetch('/read_eeprom',{method:'POST'}).then(r=>r.text()).then(t=>{toast(t);refreshStatus();});
}
function doBackup(){
  toast('Generando backup...');
  window.location.href='/backup';
}
function doRestore(){
  var fi=document.getElementById('restore-file-input');
  fi.value='';
  fi.onchange=function(){
    if(!fi.files.length) return;
    if(!confirm('Restaurar backup completo?\nSe sobrescribiran TODAS las configuraciones, presets y esquemas.\nEl ESP32 se reiniciara automaticamente.')) return;
    var fd=new FormData();
    fd.append('file',fi.files[0]);
    toast('Restaurando backup...');
    fetch('/restore',{method:'POST',body:fd}).then(r=>r.text()).then(t=>{
      toast(t);
    }).catch(function(){toast('Error de conexion');});
  };
  fi.click();
}

var eqOn=true, eqSlots=[], eqActive=-1;
  var nx=parseFloat(localStorage.getItem('eqNX')||'0'), ny=parseFloat(localStorage.getItem('eqNY')||'0'), eqEpoch=0, eqDragging=false, eqSliderBusy=false, eqSliderBusyTimer=null;
function markSliderBusy(){ eqSliderBusy=true; clearTimeout(eqSliderBusyTimer); eqSliderBusyTimer=setTimeout(function(){ eqSliderBusy=false; },600); }

function refreshEQ(){
  var snap=++eqEpoch;
  fetch('/eq/state').then(r=>r.json()).then(d=>{
    if(eqEpoch!==snap) return;
    eqOn=d.enabled; eqSlots=d.slots; eqActive=d.active;
    if(!eqDragging){ nx=d.nx; ny=d.ny; localStorage.setItem('eqNX',String(d.nx)); localStorage.setItem('eqNY',String(d.ny)); }
    if(!eqSliderBusy){
      document.getElementById('sl-bf').value = d.bassFreq;
      document.getElementById('sl-bb').value = d.bassBoost;
      document.getElementById('sl-bc').value = d.bassCompRatio;
      var f = parseFloat(d.bassFreq);
      var b = parseFloat(d.bassBoost);
      var c = parseFloat(d.bassCompRatio);
      document.getElementById('vl-bf').textContent = Math.round(f) + ' Hz';
      document.getElementById('vl-bb').textContent = (b > 0 ? '+' : '') + b.toFixed(1) + ' dB';
      document.getElementById('vl-bc').textContent = c.toFixed(1) + ' : 1';
      for(var b_idx=0;b_idx<8;b_idx++){
        var bd=d.bands[b_idx];
        document.getElementById('f'+b_idx).value=bd.freq;
        document.getElementById('g'+b_idx).value=bd.gain;
        document.getElementById('q'+b_idx).value=bd.q;
        document.getElementById('fv'+b_idx).textContent=Math.round(bd.freq)+' Hz';
        document.getElementById('gvs'+b_idx).textContent=(bd.gain>0?'+':'')+parseFloat(bd.gain).toFixed(1)+' dB';
        document.getElementById('qv'+b_idx).textContent=parseFloat(bd.q).toFixed(2);
        document.getElementById('gf'+b_idx).textContent=fmtFreq(bd.freq);
        setGv(b_idx,bd.gain);
      }
      var ibt=parseFloat(d.inputVolBT||0), ili=parseFloat(d.inputVolLineIn||0), ist=parseFloat(d.inputVolSineTone||0);
      document.getElementById('ivol-bt').value=ibt;
      document.getElementById('ivol-bt-v').textContent=(ibt>0?'+':'')+ibt.toFixed(1)+' dB';
      document.getElementById('ivol-li').value=ili;
      document.getElementById('ivol-li-v').textContent=(ili>0?'+':'')+ili.toFixed(1)+' dB';
      document.getElementById('ivol-st').value=ist;
      document.getElementById('ivol-st-v').textContent=(ist>0?'+':'')+ist.toFixed(1)+' dB';
    }
    updateEqLed(); updateMemButtons();
    if(!eqDragging){ if(padOK) movePuck(); else setTimeout(function(){ movePuck(); },120); }
  }).catch(()=>{ setTimeout(refreshEQ, 1000); });
}

function updateEqLed(){
  var btn=document.getElementById('eq-tog'), led=document.getElementById('eq-led');
  if(eqOn){
    btn.classList.add('mem-active');
  led.style.background='radial-gradient(circle at 35% 30%,#a0ffb0,#2db83a)';
    led.style.boxShadow='0 0 6px rgba(45,184,58,.9),0 0 12px rgba(45,184,58,.4)';
  } else {
    btn.classList.remove('mem-active');
  led.style.background='radial-gradient(circle at 35% 30%,#2a1808,#0e0604)';
    led.style.boxShadow='inset 0 1px 2px rgba(0,0,0,.8)';
  }
}
function toggleEq(){
  fetch('/eq/toggle').then(r=>r.text()).then(t=>{ eqOn=!eqOn; updateEqLed(); toast(t); });
  }
function resetEq(){
  fetch('/eq/reset').then(r=>r.text()).then(t=>{ toast(t); nx=0; ny=0; eqActive=-1; movePuck(); refreshEQ(); });
}

function setGv(b,v){
  var n=parseFloat(v), el=document.getElementById('gv'+b); if(!el) return;
  el.textContent=(n>0?'+':'')+n.toFixed(1);
  el.style.color=Math.abs(n)>8?'#ff8020':Math.abs(n)>0.3?'var(--g1)':'#604820';
}
function fmtFreq(f){
  if(f<1000) return Math.round(f)+'';
  var k=f/1000;
  return (k===Math.floor(k)?Math.floor(k):parseFloat(k.toFixed(1)))+'k';
}

var dbTimer = null;
function onBass(){
  markSliderBusy();
  var f = parseFloat(document.getElementById('sl-bf').value);
  var b = parseFloat(document.getElementById('sl-bb').value);
  var c = parseFloat(document.getElementById('sl-bc').value);
  document.getElementById('vl-bf').textContent = Math.round(f) + ' Hz';
  document.getElementById('vl-bb').textContent = (b > 0 ? '+' : '') + b.toFixed(1) + ' dB';
  document.getElementById('vl-bc').textContent = c.toFixed(1) + ' : 1';
  clearTimeout(dbTimer);
  dbTimer = setTimeout(() => fetch('/eq/bass?f='+f+'&b='+b+'&c='+c), 80);
}

var dt={};
  function onSl(b,type,el){
  markSliderBusy();
  var v=parseFloat(el.value);
  if(type==='f'){ document.getElementById('fv'+b).textContent=Math.round(v)+' Hz'; document.getElementById('gf'+b).textContent=fmtFreq(v); }
  if(type==='g'){ document.getElementById('gvs'+b).textContent=v.toFixed(1)+' dB'; setGv(b,v); }
  if(type==='q') document.getElementById('qv'+b).textContent=v.toFixed(2);
  clearTimeout(dt[b]);
  dt[b]=setTimeout(()=>fetch('/eq/set?band='+b
    +'&freq='+document.getElementById('f'+b).value
    +'&gain='+document.getElementById('g'+b).value
    +'&q='   +document.getElementById('q'+b).value),80);
}
function flatBand(b){
  document.getElementById('g'+b).value=0;
  document.getElementById('gvs'+b).textContent='0.0 dB'; setGv(b,0);
  fetch('/eq/set?band='+b+'&freq='+document.getElementById('f'+b).value+'&gain=0&q='+document.getElementById('q'+b).value);
}
function toggleAdv(){
  var s=document.getElementById('advSec'), b=document.getElementById('advBtn');
  s.classList.toggle('open');
  var open=s.classList.contains('open');
  b.classList.toggle('adv-open',open);
  b.innerHTML=open?'&#x2261;&ensp;Simple':'&#x2261;&ensp;Advanced';
}

var ivolTimer={};
function onInputVol(ch,el){
  markSliderBusy();
  var v=parseFloat(el.value);
  document.getElementById('ivol-'+ch+'-v').textContent=(v>0?'+':'')+v.toFixed(1)+' dB';
  clearTimeout(ivolTimer[ch]);
  ivolTimer[ch]=setTimeout(()=>fetch('/input/vol?ch='+ch+'&v='+v),80);
}

var saveMode=false;
  function updateMemButtons(){
  for(var i=0;i<5;i++){
    var b=document.getElementById('mb'+i);
    b.classList.remove('mem-active','mem-stored','mem-pick');
    if(eqSlots[i]) b.classList.add('mem-stored');
  }
  if(eqActive>=0) document.getElementById('mb'+eqActive).classList.add('mem-active');
  }
function memSave(){
  saveMode=!saveMode;
  var sb=document.getElementById('savebtn');
  if(saveMode){
    sb.classList.add('save-armed');
    for(var i=0;i<5;i++) document.getElementById('mb'+i).classList.add('mem-pick');
    toast('Elige M1\u2013M5 para guardar');
  } else {
    sb.classList.remove('save-armed');
    for(var i=0;i<5;i++) document.getElementById('mb'+i).classList.remove('mem-pick');
    toast('Cancelado');
  }
}
function memPress(slot){
  var sb=document.getElementById('savebtn');
  if(saveMode){
    saveMode=false; sb.classList.remove('save-armed');
    for(var i=0;i<5;i++) document.getElementById('mb'+i).classList.remove('mem-pick');
    fetch('/eq/mem/save?slot='+slot).then(r=>r.text()).then(t=>{
      eqSlots[slot]=true; eqActive=slot; updateMemButtons(); toast(t);
    });
  } else {
    if(!eqSlots[slot]){toast('Slot M'+(slot+1)+' vacío');return;}
    fetch('/eq/mem/load?slot='+slot).then(r=>r.text()).then(t=>{ eqActive=slot; toast(t); refreshEQ(); });
  }
}

var R=126, cx=126, cy=126, padOK=false, xyTimer=null;
var movePuck=function(){};
var padUpdate=function(){};

function sendXY(){ localStorage.setItem('eqNX',String(nx)); localStorage.setItem('eqNY',String(ny)); fetch('/eq/xy?nx='+nx.toFixed(4)+'&ny='+ny.toFixed(4)); }

function goBand(b){
  go('adv');
  setTimeout(function(){
    var card=document.getElementById('eqcard'+b);
    if(!card) return;
    var sb=card.closest('.sec-body');
    var needOpen=sb&&sb.classList.contains('closed');
    if(needOpen){
      var st=sb.previousElementSibling;
      if(st) toggleSec(st);
    }
    setTimeout(function(){
      card.scrollIntoView({behavior:'smooth',block:'center'});
      setTimeout(function(){
        card.style.transition='box-shadow 0.2s ease-in';
        card.style.boxShadow='0 0 0 2px #ffcc60,0 0 24px rgba(255,200,80,0.7)';
        setTimeout(function(){
          card.style.transition='box-shadow 0.6s ease-out';
          card.style.boxShadow='';
        },400);
        var sl=document.getElementById('g'+b); if(sl) sl.focus();
      },450);
    }, needOpen ? 350 : 30);
  },80);
}

function initPad(){
  if(padOK) return; padOK=true;
  var cv=document.getElementById('pad'), pk=document.getElementById('puck');
  var ctx=cv.getContext('2d');

  function sc(){ var r=cv.getBoundingClientRect(); return {x:cv.width/r.width, y:cv.height/r.height}; }

  function draw(){
    ctx.clearRect(0,0,252,252);
  var alpha=Math.sqrt(nx*nx+ny*ny), gx=cx+nx*R, gy=cy-ny*R;
    var gl=ctx.createRadialGradient(gx,gy,0,cx,cy,R);
    gl.addColorStop(0,'rgba(255,160,40,'+(0.28*alpha)+')');
    gl.addColorStop(0.5,'rgba(200,100,20,'+(0.1*alpha)+')');
    gl.addColorStop(1,'rgba(160,80,0,0)');
    ctx.fillStyle=gl; ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fill();
    var disc=ctx.createRadialGradient(cx-20,cy-25,8,cx,cy,R);
    disc.addColorStop(0,'#2a1c0c'); disc.addColorStop(0.4,'#1c1206');
    disc.addColorStop(0.8,'#140e04'); disc.addColorStop(1,'#0e0802');
    ctx.fillStyle=disc;
  ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fill();
    ctx.save(); ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.clip();
    for(var i=-R;i<R;i+=7){ ctx.strokeStyle='rgba(160,80,20,0.06)'; ctx.lineWidth=0.5; ctx.beginPath(); ctx.moveTo(cx-R,cy+i); ctx.lineTo(cx+R,cy+i); ctx.stroke();
  }
    ctx.restore();[0.25,0.5,0.75,1.0].forEach(function(f,ri){ ctx.strokeStyle=ri===3?'rgba(200,146,42,0.35)':'rgba(200,146,42,0.15)'; ctx.lineWidth=ri===3?.8:.5; ctx.beginPath(); ctx.arc(cx,cy,R*f,0,2*Math.PI); ctx.stroke(); });
    for(var t=0;t<72;t++){ var ang=t/72*2*Math.PI, big=(t%9===0), r0=R*(big?.88:.92); ctx.strokeStyle=big?'rgba(200,146,42,0.5)':'rgba(200,146,42,0.2)'; ctx.lineWidth=big?1:.5; ctx.beginPath();
  ctx.moveTo(cx+Math.cos(ang)*r0,cy+Math.sin(ang)*r0); ctx.lineTo(cx+Math.cos(ang)*(R-1),cy+Math.sin(ang)*(R-1)); ctx.stroke(); }
    ctx.strokeStyle='rgba(200,146,42,0.2)'; ctx.lineWidth=0.6;
    ctx.beginPath(); ctx.moveTo(cx,cy-R); ctx.lineTo(cx,cy+R); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(cx-R,cy); ctx.lineTo(cx+R,cy); ctx.stroke();
    if(alpha>0.04){ var tr=ctx.createLinearGradient(cx,cy,gx,gy);
  tr.addColorStop(0,'rgba(200,146,42,0)'); tr.addColorStop(1,'rgba(255,180,60,0.45)'); ctx.strokeStyle=tr; ctx.lineWidth=1.5; ctx.setLineDash([4,7]); ctx.beginPath(); ctx.moveTo(cx,cy); ctx.lineTo(gx,gy); ctx.stroke(); ctx.setLineDash([]); }
    ctx.strokeStyle='rgba(200,146,42,0.5)'; ctx.lineWidth=0.8;
    ctx.beginPath(); ctx.arc(cx,cy,5,0,2*Math.PI); ctx.stroke();
    ctx.beginPath();
  ctx.moveTo(cx-8,cy); ctx.lineTo(cx+8,cy); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(cx,cy-8); ctx.lineTo(cx,cy+8); ctx.stroke();
  }

  movePuck=function(){
    var s=sc();
    pk.style.left=(cx+nx*R)/s.x+'px';
    pk.style.top=(cy-ny*R)/s.y+'px';
    draw();
  };
  padUpdate=function(){
    movePuck();
    var padGains=[
       ny*7,
       ny*5-nx*2,
      -nx*3,
      -nx*4,
       nx*4,
       nx*3,
      -ny*4+nx*2,
      -ny*7
    ];
  padGains.forEach(function(g,b){
      var gv=Math.max(-12,Math.min(12,g));
      setGv(b,gv);
      var sl=document.getElementById('g'+b);
      var lbl=document.getElementById('gvs'+b);
      if(sl)  sl.value=gv;
      if(lbl) lbl.textContent=(gv>0?'+':'')+gv.toFixed(1)+' dB';
    });
  };

  var drag=false;
  function pos(clientX,clientY){
    var rc=cv.getBoundingClientRect(), s=sc();
    var dx=(clientX-rc.left)*s.x-cx, dy=(clientY-rc.top)*s.y-cy;
    var d=Math.sqrt(dx*dx+dy*dy);
  if(d>R){dx=dx/d*R;dy=dy/d*R;}
    nx=dx/R; ny=-dy/R; padUpdate();
    clearTimeout(xyTimer); xyTimer=setTimeout(sendXY,80);
  }
  cv.addEventListener('mousedown',e=>{e.preventDefault();drag=true;eqDragging=true;pos(e.clientX,e.clientY);
    var mm=e=>{if(drag)pos(e.clientX,e.clientY);};
    var mu=()=>{drag=false;eqDragging=false;document.removeEventListener('mousemove',mm);document.removeEventListener('mouseup',mu);};
    document.addEventListener('mousemove',mm); document.addEventListener('mouseup',mu);});
  cv.addEventListener('touchstart',e=>{e.preventDefault();drag=true;eqDragging=true;pos(e.touches[0].clientX,e.touches[0].clientY);},{passive:false});
  cv.addEventListener('touchmove',e=>{e.preventDefault();if(drag)pos(e.touches[0].clientX,e.touches[0].clientY);},{passive:false});
  cv.addEventListener('touchend',()=>{drag=false;eqDragging=false;});
  movePuck();
}

function fmtAddr(n){ return '0x'+('000'+parseInt(n).toString(16).toUpperCase()).slice(-4); }
function parseAddr(v){
  v=v.trim(); if(!v) return null;
  var n=/^0x/i.test(v)?parseInt(v,16):parseInt(v,10);
  return isNaN(n)?null:n;
}

function toggleSec(el){
  el.classList.toggle('closed');
  el.nextElementSibling.classList.toggle('closed');
}

function refreshConfig(){
  fetch('/status').then(r=>r.json()).then(d=>{
    document.getElementById('cfg-ssid').value     = d.ssid||'';
    document.getElementById('cfg-hostname').value = d.hostname||'';
    document.getElementById('cfg-ap-ssid').value  = d.apSSID||'';
    document.getElementById('cfg-tcp-port').value = d.tcpPort||8086;
    document.getElementById('cfg-dsp-addr').value = d.dspI2cAddr ? '0x'+parseInt(d.dspI2cAddr).toString(16).toUpperCase() : '0x34';
    document.getElementById('cfg-vu-win').value   = d.vuWindowMs||250;
  });
  fetch('/eq/state').then(r=>r.json()).then(d=>{
    for(var b=0;b<8;b++) document.getElementById('cfg-a'+b).value=fmtAddr(d.bands[b].addr);
    document.getElementById('cfg-bfa').value  = fmtAddr(d.addrBassFreq);
    document.getElementById('cfg-bba').value  = fmtAddr(d.addrBassBoost);
    document.getElementById('cfg-bca').value  = fmtAddr(d.addrBassComp);
    document.getElementById('cfg-ivbt').value = fmtAddr(d.addrInputVolBT);
    document.getElementById('cfg-ivli').value = fmtAddr(d.addrInputVolLineIn);
    document.getElementById('cfg-ivst').value = fmtAddr(d.addrInputVolSineTone);
    document.getElementById('cfg-vul').value  = fmtAddr(d.addrVuL);
    document.getElementById('cfg-vur').value  = fmtAddr(d.addrVuR);
    document.getElementById('cfg-stlm').value = fmtAddr(d.addrSineLMask);
    document.getElementById('cfg-stli').value = fmtAddr(d.addrSineLFreq);
    document.getElementById('cfg-stlo').value = fmtAddr(d.addrSineLIson);
    document.getElementById('cfg-strm').value = fmtAddr(d.addrSineRMask);
    document.getElementById('cfg-stri').value = fmtAddr(d.addrSineRFreq);
    document.getElementById('cfg-stro').value = fmtAddr(d.addrSineRIson);
  });
  fetch('/config/pins').then(r=>r.json()).then(d=>{
    document.getElementById('cfg-scl').value=d.scl;
    document.getElementById('cfg-sda').value=d.sda;
    document.getElementById('cfg-rst').value=d.rst;
    document.getElementById('cfg-sb').value=d.sb;
    document.getElementById('cfg-led').value=d.led;
  }).catch(()=>{});
  }

var curRamSrc=-1, curEpmSrc=-1;
function refreshSchemasUI() {
  fetch('/schema/list').then(r=>r.json()).then(d=>{
    for(var i=0; i<4; i++) {
        var btnRam = document.getElementById('btn-ram-s'+i);
        var btnEpm = document.getElementById('btn-epm-s'+i);
        btnRam.classList.remove('mem-active');
        btnEpm.classList.remove('mem-active');
        var btnDl = document.getElementById('btn-dl-s'+i);
        if(d[i]) {
            btnRam.classList.add('mem-stored'); btnRam.innerHTML = 'RAM B' + (i+1);
            btnEpm.classList.add('mem-stored'); btnEpm.innerHTML = 'EPM B' + (i+1);
            if(btnDl){ btnDl.classList.add('mem-stored'); btnDl.innerHTML = '&#x2B07; B' + (i+1); }
        } else {
            btnRam.classList.remove('mem-stored'); btnRam.innerHTML = '---';
            btnEpm.classList.remove('mem-stored'); btnEpm.innerHTML = '---';
            if(btnDl){ btnDl.classList.remove('mem-stored'); btnDl.innerHTML = '---'; }
        }
        if(curRamSrc === i) btnRam.classList.add('mem-active');
        if(curEpmSrc === i) btnEpm.classList.add('mem-active');
    }
  }).catch(()=>{});
}
function updateActiveSources(ram, epm){
  curRamSrc = ram; curEpmSrc = epm;
  var info = document.getElementById('schema-active-info');
  var parts = [];
  // marcar LEDs
  for(var i=0;i<4;i++){
    var br=document.getElementById('btn-ram-s'+i);
    var be=document.getElementById('btn-epm-s'+i);
    if(br){ br.classList.remove('mem-active'); if(ram===i) br.classList.add('mem-active'); }
    if(be){ be.classList.remove('mem-active'); if(epm===i) be.classList.add('mem-active'); }
  }
  // texto RAM
  if(ram>=0 && ram<=3) parts.push('RAM: <b style="color:var(--am2)">Banco '+(ram+1)+'</b>');
  else if(ram===99) parts.push('RAM: <b style="color:var(--am2)">SigmaStudio</b>');
  // texto EEPROM
  if(epm>=0 && epm<=3) parts.push('EEPROM: <b style="color:var(--g1)">Banco '+(epm+1)+'</b>');
  info.innerHTML = parts.length ? '&#x25B6; '+parts.join(' &ensp;|&ensp; ') : '';
}

function loadSchema(slot, toRam) {
  var id = toRam ? 'btn-ram-s'+slot : 'btn-epm-s'+slot;
  if(document.getElementById(id).innerHTML === '---') return;
  var msg = toRam ? '¿Cargar el Banco ' + (slot+1) + ' a la RAM del DSP? (Temporal)' 
                  : '¿Grabar el Banco ' + (slot+1) + ' en la EEPROM? (Permanente)';
  if(!confirm(msg)) return;
  var p=new URLSearchParams(); p.append('slot', slot);
  if(toRam) p.append('ram', '1');
  fetch('/schema/load', {method:'POST', body:p}).then(r=>r.text()).then(t=>{
    toast(t);
    refreshStatus();
    refreshConfig();
    refreshSchemasUI();
  });
}

function saveSchema(slot) {
  if(!capReady) { toast('Error: No hay captura en RAM. Descarga desde SigmaStudio primero.'); return; }
  var p=new URLSearchParams(); p.append('slot', slot);
  fetch('/schema/save', {method:'POST', body:p}).then(r=>r.text()).then(t=>{
    toast(t);
    refreshSchemasUI();
  });
}

function dlSchema(slot){
  var btn=document.getElementById('btn-dl-s'+slot);
  if(!btn||btn.innerHTML.indexOf('---')>=0){ toast('Banco '+(slot+1)+' vacio'); return; }
  window.location.href='/schema/download?slot='+slot;
}
var _ulSlot=-1;
function ulSchema(slot){
  _ulSlot=slot;
  var fi=document.getElementById('schema-file-input');
  fi.value='';
  fi.onchange=function(){
    if(!fi.files.length) return;
    var fd=new FormData();
    fd.append('file',fi.files[0]);
    toast('Importando Banco '+(slot+1)+'...');
    fetch('/schema/upload?slot='+slot,{method:'POST',body:fd}).then(r=>r.text()).then(t=>{
      toast(t);
      refreshSchemasUI();
    });
  };
  fi.click();
}

function saveWifi(){
  var p=new URLSearchParams();
  p.append('ssid',document.getElementById('cfg-ssid').value);
  p.append('pass',document.getElementById('cfg-pass').value);
  fetch('/save_wifi',{method:'POST',body:p}).then(()=>toast('WiFi guardado — reiniciando...'));
}
function saveNetwork(){
  var p=new URLSearchParams();
  p.append('hostname', document.getElementById('cfg-hostname').value);
  p.append('ap_ssid',  document.getElementById('cfg-ap-ssid').value);
  var ap=document.getElementById('cfg-ap-pass').value; if(ap) p.append('ap_pass',ap);
  p.append('ota_pass', document.getElementById('cfg-ota-pass').value);
  p.append('tcp_port', document.getElementById('cfg-tcp-port').value);
  fetch('/save_network',{method:'POST',body:p}).then(r=>r.text()).then(t=>toast(t));
}
function savePins(){
  var p=new URLSearchParams();['scl','sda','rst','sb','led'].forEach(k=>p.append(k,document.getElementById('cfg-'+k).value));
  fetch('/save_pins',{method:'POST',body:p}).then(()=>toast('Pins guardados — reiniciando...'));
}
function saveDsp(){
  var p=new URLSearchParams();
  var da=parseAddr(document.getElementById('cfg-dsp-addr').value);
  if(da===null){toast('Dirección DSP inválida');return;}
  p.append('dsp_addr', da);
  // Incluir también VU y vu_win para no sobrescribir con valores vacíos
  var vul=parseAddr(document.getElementById('cfg-vul').value);
  var vur=parseAddr(document.getElementById('cfg-vur').value);
  var win=parseInt(document.getElementById('cfg-vu-win').value);
  if(vul!==null) p.append('vul', vul);
  if(vur!==null) p.append('vur', vur);
  if(!isNaN(win)&&win>=50&&win<=2000) p.append('vu_win', win);
  fetch('/save_eq_addrs',{method:'POST',body:p}).then(r=>r.text()).then(t=>toast(t));
}
function saveAddrs(){
  var p=new URLSearchParams();
  var da=parseAddr(document.getElementById('cfg-dsp-addr').value);
  if(da===null){toast('Direcci\u00f3n DSP inv\u00e1lida');return;}
  p.append('dsp_addr', da);
  var ok=true;
  for(var b=0;b<8;b++){
    var v=parseAddr(document.getElementById('cfg-a'+b).value);
    if(v===null){toast('Dirección Band '+(b+1)+' inválida');ok=false;break;}
    p.append('a'+b, v);
  }
  if(!ok) return;
  var fields=[['bfa','cfg-bfa'],['bba','cfg-bba'],['bca','cfg-bca'],
              ['ivbt','cfg-ivbt'],['ivli','cfg-ivli'],['ivst','cfg-ivst'],['vul','cfg-vul'],['vur','cfg-vur'],
              ['stlm','cfg-stlm'],['stli','cfg-stli'],['stlo','cfg-stlo'],
              ['strm','cfg-strm'],['stri','cfg-stri'],['stro','cfg-stro']];
  for(var i=0;i<fields.length;i++){
    var fv=parseAddr(document.getElementById(fields[i][1]).value);
    if(fv===null){toast('Dirección '+fields[i][0]+' inválida');return;}
    p.append(fields[i][0], fv);
  }
  var win=parseInt(document.getElementById('cfg-vu-win').value);
  if(!isNaN(win)&&win>=50&&win<=2000) p.append('vu_win', win);
  fetch('/save_eq_addrs',{method:'POST',body:p}).then(r=>r.text()).then(t=>toast(t));
}
function clearPresets(){
  if(!confirm('Borrar todos los presets M1-M5?')) return;
  fetch('/eq/mem/clear',{method:'POST'}).then(r=>r.text()).then(t=>{
    eqSlots=[]; eqActive=-1; updateMemButtons(); toast(t);
  });
  }
function factoryReset(){
  if(!confirm('Borrar toda la configuración y volver a AP mode?')) return;
  fetch('/factory_reset',{method:'POST'}).then(()=>toast('Configuración borrada — AP mode'));
}

document.getElementById('paramFileInput').addEventListener('change',function(e){
  var f=e.target.files[0]; if(!f) return;
  document.getElementById('paramFileName').textContent=f.name;
  processSigmaFile(f);
});
function processSigmaFile(file) {
  if (!file) return;
  var reader = new FileReader();
  reader.onload = function(e) {
    var text = e.target.result;
    var count = 0;
    function rx(pattern, isHex) {
      var m = pattern.exec(text);
      if (m && m[1]) { count++; return isHex ? parseInt(m[1],16) : parseInt(m[1],10); }
      return null;
    }
    function setField(id, val) { if(val!==null) document.getElementById(id).value='0x'+val.toString(16).toUpperCase().padStart(4,'0'); }

    // EQ Bands A0-A7
    for (var i = 0; i < 8; i++) {
      setField('cfg-a'+i, rx(new RegExp('#define\\s+MOD_WEBEQ_ALG0_STAGE'+i+'_B0_ADDR\\s+(\\d+)')));
    }
    // Bass
    setField('cfg-bfa', rx(/#define\s+MOD_BASSBOOST1_ALG0_BASSFREQUENCY_ADDR\s+(\d+)/));
    setField('cfg-bba', rx(/#define\s+MOD_BASSBOOST1_ALG0_B0_ADDR\s+(\d+)/));
    setField('cfg-bca', rx(/#define\s+MOD_BASSBOOST1_ALG0_TABLE0_ADDR\s+(\d+)/));
    // Input Volumes
    setField('cfg-ivli', rx(/#define\s+MOD_STMIXER1_ALG0_STAGE0_VOLUME_ADDR\s+(\d+)/));
    setField('cfg-ivbt', rx(/#define\s+MOD_STMIXER1_ALG0_STAGE1_VOLUME_ADDR\s+(\d+)/));
    setField('cfg-ivst', rx(/#define\s+MOD_STMIXER1_ALG0_STAGE2_VOLUME_ADDR\s+(\d+)/));
    // VU Meters (hex values)
    setField('cfg-vul', rx(/#define\s+MOD_READBACK1_ALG0_VAL0_VALUES[\s\S]*?SIGMASTUDIOTYPE_SPECIAL\s*\(\s*(0x[0-9A-Fa-f]+)\s*\)/, true));
    setField('cfg-vur', rx(/#define\s+MOD_READBACK2_ALG0_VAL0_VALUES[\s\S]*?SIGMASTUDIOTYPE_SPECIAL\s*\(\s*(0x[0-9A-Fa-f]+)\s*\)/, true));
    // Sine Tone L
    setField('cfg-stlm', rx(/#define\s+MOD_\w*TONE_?L\d*_ALG0_MASK_ADDR\s+(\d+)/));
    setField('cfg-stli', rx(/#define\s+MOD_\w*TONE_?L\d*_ALG0_INCREMENT_ADDR\s+(\d+)/));
    setField('cfg-stlo', rx(/#define\s+MOD_\w*TONE_?L\d*_ALG0_(?:IS)?ON_ADDR\s+(\d+)/));
    // Sine Tone R
    setField('cfg-strm', rx(/#define\s+MOD_\w*TONE_?R\d*_ALG0_MASK_ADDR\s+(\d+)/));
    setField('cfg-stri', rx(/#define\s+MOD_\w*TONE_?R\d*_ALG0_INCREMENT_ADDR\s+(\d+)/));
    setField('cfg-stro', rx(/#define\s+MOD_\w*TONE_?R\d*_ALG0_(?:IS)?ON_ADDR\s+(\d+)/));

    var total = 22;
    if (count === total) toast(file.name+': '+count+'/'+total+' params OK — pulsa Save para guardar');
    else toast(file.name+': '+count+'/'+total+' params encontrados — revisa los campos');
  };
  reader.readAsText(file);
}

var logTimer=null, logLastCount=0;

// ── SSE — recibir eventos en tiempo real del ESP32 ────────────
function applyStatus(d){
  if(!d) return;
  if(typeof d.vuL!=='undefined'){
    vuTargetL=d.vuL;
    vuTargetR=d.vuR;
    vuLastSseMs=Date.now();
  }
  if(typeof d.dspRunning==='undefined') return; // Si es un update rápido de VU, terminar aquí.
  
  if(d.fwVersion){
    var fv=document.getElementById('fw-ver');if(fv) fv.textContent='v'+d.fwVersion;
    var fv2=document.getElementById('sv-fw-ver2');if(fv2) fv2.textContent='v'+d.fwVersion+(d.fwDate?' ('+d.fwDate+')':'');
  }
  document.getElementById('sv-ip').textContent=d.ip||'—';
  document.getElementById('sv-net').textContent=d.ssid||'AP Mode';
  var hn=d.hostname||'—';
  document.getElementById('sv-ota-host').textContent=hn;
  var h2=document.getElementById('sv-ota-host2'); if(h2) h2.textContent=hn;
  document.getElementById('sv-dsp').innerHTML=d.dspRunning
    ?'<span class="led led-g"></span><span class="on">RUNNING</span>'
    :'<span class="led led-x"></span><span class="off">STOPPED</span>';
  var tc=d.tcpConnected;
  document.getElementById('tcp-led').className='led '+(tc?'led-g':'led-x');
  document.getElementById('tcp-t').textContent=tc?'Conectado':'Desconectado';
  document.getElementById('tcp-t').className=tc?'on':'off';
  var logOn=d.logEnabled;
  var logLed=document.getElementById('log-led');
  var logTxt=document.getElementById('log-t');
  if(logLed) logLed.className='led '+(logOn?'led-o':'led-x');
  if(logTxt){ logTxt.textContent=logOn?'ON':'OFF'; logTxt.className=logOn?'hot':'off'; }
  var eb=d.eqBootEnabled;
  document.getElementById('eqboot-led').className='led '+(eb?'led-g':'led-x');
  document.getElementById('eqboot-t').textContent=eb?'ON':'OFF';
  document.getElementById('eqboot-t').className=eb?'on':'off';
  document.getElementById('eqboot-btn').innerHTML=eb?'&#x23CF;&ensp;EQ Boot ON':'&#x23CF;&ensp;EQ Boot OFF';
  var capEl=document.getElementById('sv-cap');
  if(d.captureReady) {
    capEl.innerHTML='<span class="led led-g"></span><span class="on">READY</span>&ensp;<span class="badge">'+d.captureLen+' B</span>';
    document.getElementById('schema-save-row').style.display='flex';
  } else if(d.captureLen>0) {
    capEl.innerHTML='<span class="led led-o"></span><span class="hot">DOWNLOADING</span>&ensp;<span class="badge">'+d.captureLen+' B</span>';
    document.getElementById('schema-save-row').style.display='none';
  } else {
    capEl.innerHTML='<span class="led led-x"></span><span class="off">Waiting Download</span>';
    document.getElementById('schema-save-row').style.display='none';
  }
  document.getElementById('eeprom-row').style.display=d.captureReady?'':'none';
  document.getElementById('eeprom-warn').style.display=d.captureReady?'none':'';
  var lk=d.dspLocked;
  document.getElementById('dsplock-led').className='led '+(lk?'led-o':'led-x');
  document.getElementById('dsplock-t').textContent=lk?'ON':'OFF';
  document.getElementById('dsplock-t').className=lk?'hot':'off';
  var lb=document.getElementById('dsplock-btn');
  lb.innerHTML=lk?'&#x1F512;&ensp;DSP Lock ON':'&#x1F513;&ensp;DSP Lock OFF';
  lb.className='pbtn '+(lk?'pbtn-red':'pbtn-dark');
  // ── Mute button ──
  var mb=document.getElementById('mute-btn');
  if(mb){
    var mt=d.dspMuted;
    mb.innerHTML=mt?'&#x1F507; MUTE':'&#x1F50A; ON';
    mb.className='mute-btn'+(mt?' muted':'');
  }
  // ── Line Mute button ──
  var lmb=document.getElementById('line-mute-btn');
  if(lmb){
    var lm=d.lineMuted;
    lmb.innerHTML=lm?'&#x1F507; MUTE':'&#x1F50A; ON';
    lmb.className='pbtn '+(lm?'pbtn-red':'pbtn-dark');
    lmb.style.cssText='float:right;padding:4px 10px;font-size:9px;min-width:auto;';
  }
  if(typeof d.activeRam!=='undefined') updateActiveSources(d.activeRam, d.activeEeprom);
  // ── Sleep overlay ──
  if(typeof d.sleepPending!=='undefined'){
    var ov=document.getElementById('sleep-overlay');
    if(d.sleepPending){
      document.body.classList.add('sleeping');
      if(ov){ ov.style.display='flex'; ov.querySelector('.sleep-sec').textContent=d.sleepCountdown; }
    } else {
      document.body.classList.remove('sleeping');
      if(ov) ov.style.display='none';
    }
  }
}
(function startSSE(){
  var es = new EventSource('/events');
  es.onmessage = function(e){ try{ applyStatus(JSON.parse(e.data)); }catch(ex){} };
  es.onerror   = function(){ setTimeout(startSSE, 1000); es.close(); };
})();
  function fetchLog(){
  fetch('/log').then(r=>r.json()).then(lines=>{
    if(lines.length===logLastCount) return;
    logLastCount=lines.length;
    var c=document.getElementById('log-console');
    if(!c) return;
    var atBottom=c.scrollHeight-c.scrollTop<=c.clientHeight+20;
    c.textContent=lines.join('\n');
    if(atBottom) c.scrollTop=c.scrollHeight;
  }).catch(()=>{});
  }
function toggleLogAuto(){
  var on=document.getElementById('log-auto').checked;
  if(on){ logTimer=setInterval(fetchLog,800); fetchLog(); }
  else { clearInterval(logTimer); logTimer=null; }
}
function clearLogDisplay(){
  var c=document.getElementById('log-console');
  if(c) c.textContent='';
  logLastCount=0;
}
// log polling siempre activo — no se para al cambiar de pestana

function doHttpOta(){
  var f=document.getElementById('bin-file').files[0];
  if(!f){toast('Selecciona un archivo .bin');return;}
  if(!f.name.endsWith('.bin')){toast('El archivo debe ser .bin');return;}
  var bar=document.getElementById('ota-bar');
  var wrap=document.getElementById('ota-bar-wrap');
  var st=document.getElementById('ota-status');
  wrap.style.display='block';
  bar.style.width='0%';
  st.textContent='Subiendo '+f.name+' ('+Math.round(f.size/1024)+' KB)...';
  st.style.color='var(--am)';
  var fd=new FormData();
  fd.append('firmware',f,f.name);
  var xhr=new XMLHttpRequest();
  xhr.open('POST','/update',true);
  xhr.upload.onprogress=function(e){
    if(e.lengthComputable){
      var pct=Math.round(e.loaded/e.total*100);
      bar.style.width=pct+'%';
      st.textContent='Subiendo... '+pct+'%';
    }
  };
  xhr.onload=function(){
    if(xhr.status===200){
      bar.style.width='100%';
      bar.style.background='linear-gradient(90deg,#2a8020,#60d040)';
      st.textContent='OK — reiniciando...';
      st.style.color='#60d040';
      toast('Firmware actualizado — reiniciando...');
  } else {
      st.textContent='Error: '+xhr.responseText;
      st.style.color='#e05050';
      toast('Error OTA: '+xhr.responseText);
    }
  };
  xhr.onerror=function(){
    st.textContent='Error de conexión';
    st.style.color='#e05050';
    toast('Error de conexión');
  };
  xhr.send(fd);
}

window.addEventListener('DOMContentLoaded',function(){ initVUBars(); startVU(); go(localStorage.getItem('activeTab')||'eq'); });
  </script>
</body></html>
)HTMLEOF";
