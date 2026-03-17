import asyncio

async def handle_echo(reader, writer):
    """Callback funkce pro každého připojeného klienta."""
    addr = writer.get_extra_info('peername')
    print(f"[Server] Přijato spojení od {addr}")

    while True:
        data = await reader.read(1024)
        if not data:
            break
            
        message = data.decode()
        print(f"[Server] Přijato: {message!r} od {addr}")

        print(f"[Server] Odesílám echo...")
        writer.write(data)
        await writer.drain()

    print(f"[Server] Zavírám spojení s {addr}")
    writer.close()
    await writer.wait_closed()

async def main():
    server = await asyncio.start_server(
        handle_echo, '127.0.0.1', 8888)

    addrs = ', '.join(str(sock.getsockname()) for sock in server.sockets)
    print(f'--- ASYNC ECHO SERVER běží na {addrs} ---')

    async with server:
        await server.serve_forever()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n[Server] Vypínám...")
