#!/usr/bin/env python3
"""
Simple WebSocket Echo Server for testing
Install: pip install websockets
Run: python test_echo_server.py
"""

import asyncio
import websockets

async def echo(websocket):
    print(f"Client connected from {websocket.remote_address}")
    try:
        async for message in websocket:
            print(f"Received: {message}")
            await websocket.send(f"Echo: {message}")
            print(f"Sent: Echo: {message}")
    except websockets.exceptions.ConnectionClosed:
        print("Client disconnected")

async def main():
    print("Starting WebSocket echo server on ws://localhost:8080")
    async with websockets.serve(echo, "localhost", 8080):
        await asyncio.Future()  # run forever

if __name__ == "__main__":
    asyncio.run(main())

