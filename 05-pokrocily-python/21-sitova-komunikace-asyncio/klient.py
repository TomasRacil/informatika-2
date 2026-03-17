import asyncio

async def tcp_echo_client(message):
    print(f'[Klient] Připojuji se k serveru na 127.0.0.1:8888...')
    try:
        reader, writer = await asyncio.open_connection(
            '127.0.0.1', 8888)

        print(f'[Klient] Odesílám: {message!r}')
        writer.write(message.encode())
        await writer.drain()

        data = await reader.read(100)
        print(f'[Klient] Přijato: {data.decode()!r}')

        print('[Klient] Zavírám spojení...')
        writer.close()
        await writer.wait_closed()
    except ConnectionRefusedError:
        print('[Klient] CHYBA: Server neběží na 127.0.0.1:8888')

if __name__ == "__main__":
    zprava = 'Ahoj z asynchronního klienta!'
    asyncio.run(tcp_echo_client(zprava))
