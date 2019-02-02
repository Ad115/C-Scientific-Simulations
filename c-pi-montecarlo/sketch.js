var state = {"coords": [0,0], "pi":0};
var already_drawn = true;


// --- Receive the simulation data

var ws = new WebSocket("ws://127.0.0.1:5678/");

ws.onmessage = function (event) {
               state = JSON.parse(event.data);
               already_drawn = false;
            };


// --- Helper functions
            
function toScreenPos(pos) {
    return [width * (0.5 + pos[0]/2), 
            height * (0.5 + pos[1]/2)];
}

function fetchColor(pos) {
    x = pos[0];
    y = pos[1];
    r = sqrt(x*x + y*y)
    if (r < 1) {
        return 255;
    } else {
        return 50;
    }
}


// --- Drawing functions

function setup() {
    createCanvas(600, 600);
    background(200);
    fill(100);
    noStroke();
}

function draw() {      //  < --- MAIN DRAWING LOOP
    if (!already_drawn) {
        
        // < -- Draw the particle
        let pos = toScreenPos(state.coords);
        let color = fetchColor(state.coords);
        
        fill(color, 100);
        ellipse(pos[0], pos[1], 10, 10);   
        fill(color);
        ellipse(pos[0], pos[1], 5, 5);
        
        // < -- Draw the text label
        let txt = "Pi = " + state.pi;
        fill(200);
        rect(0, 1, textWidth(txt), 15);
        fill(0);
        text(txt, 0, 13);
    }
}
