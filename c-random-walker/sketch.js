var positions = [];
var screenPositions = [];


// --- Receive the simulation data

var ws = new WebSocket("ws://127.0.0.1:5678/");

ws.onmessage = function (event) {
                positions = JSON.parse(event.data);
                print(positions);
            };

            
// --- Helper functions
            
function toScreenPos(pos, idx, posArray) {
    return [width/2 + pos[0], 
            height/2 + pos[1]];
}

function fetchColor(i) {
    return 255 * noise(1000*i + 0.001*frameCount );
}


// --- Drawing functions

function setup() {
    createCanvas(600, 600);
    background(200);
    fill(100);
    noStroke();
}

function draw() {      //  < --- MAIN DRAWING LOOP
    //background(200);
    screenPositions = positions.map(toScreenPos);
    n = screenPositions.length;
    
    for (i=0; i<n; i++) {
        fill(fetchColor(i));
        
        screenPos = screenPositions[i];
        ellipse(screenPos[0], screenPos[1], 5, 5);   
    }
}
