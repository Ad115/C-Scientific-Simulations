var ising = {"spins":[[]], "energy":0};


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

function screenPosition(i, j, rows, cols) {
    return [ 
        height/(rows+1) * (i+1), 
        width/(cols+1) * (j+1) 
    ]
}


// --- Drawing functions

function setup() {
    createCanvas(600, 600);
    background(50);
    fill(100);
    noStroke();
}

function draw() {
    background(50);
        
    let spins = ising.spins;
    let rows = spins.length;
    let cols = spins[0].length;
    
        
    for (let i=0; i<rows; i++) {
        for (let j=0; j<cols; j++) {
            
            let screenPos = [
                 height/(rows+1) * (i+1), 
                 width/(cols+1) * (j+1) 
            ];
                
            let c = fetchColor(spins[i][j]);
                
            for (let k=0; k<3; k++) {
                let size = 50 * noise((frameCount + 100*j + 1000*i + 10000*k) * 0.01);
                
                fill(red(c), green(c), blue(c), 100);
                ellipse(screenPos[0], screenPos[1], size, size);
            }
        }
    }
}
