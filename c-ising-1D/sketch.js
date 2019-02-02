var ising = {"spins":[], "energy":0};
const tau = 2 * 3.1415926;


// --- Receive the simulation data

var ws = new WebSocket("ws://127.0.0.1:5678/");

ws.onmessage = function (event) {
                ising = JSON.parse(event.data);
            };


// --- Helper functions
            
function fetchColor(spin) {
    if (spin > 0) {
        return color(200, 220, 0);
    } else {
        return color(255, 0, 50)
    }
}

function setup() {
    createCanvas(600, 600);
    background(50);
    fill(100);
    noStroke();
}


// --- Drawing functions

function draw() {
    background(50);
        
    let spins = ising.spins;
    let n = spins.length;
        
    for (let i=0; i<n; i++) {
            
        let screenPos = [
            width/2 + 0.4 * width * cos(i * tau/n), 
            height/2 + 0.4 * height * sin(i * tau/n)
        ];
            
        let c = fetchColor(spins[i]);
            
        for (let j=0; j<3; j++) {
            let size = 70 * noise((frameCount+ 100*j + 1000*i) * 0.01);
            
            fill(red(c), green(c), blue(c), 100);
            ellipse(screenPos[0], screenPos[1], size, size);
        }
    }
}
