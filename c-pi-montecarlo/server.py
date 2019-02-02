#!/usr/bin/env python3

# WS server that serves the state of the Pi calculation.

import asyncio
import json
import websockets
import sys


async def loop(websocket, path):
    
    for data in sys.stdin:
            await websocket.send(data)
            await asyncio.sleep(0.05)
# ---


start_server = websockets.serve(loop, '127.0.0.1', 5678)
event_loop = asyncio.get_event_loop()

event_loop.run_until_complete(start_server)
event_loop.run_forever()
