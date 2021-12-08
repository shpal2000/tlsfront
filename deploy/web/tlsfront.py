import os
import aiohttp, json
from aiohttp import web
import asyncio
import json

gstats = {}

async def index_handle(request):
    return web.FileResponse('public/index.html')

async def api_handle(request):
    return web.json_response(gstats)

app = web.Application()

app.add_routes([web.static('/build', 'public/build')])
app.add_routes([web.static('/assets', 'public/assets')])
app.add_routes([web.route('*', '/api/{api_path:.*}', api_handle)])
app.add_routes([web.route('get', '/{tail:.*}', index_handle)])

class StatsListener:
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = data.decode()
        stats = json.loads(message)
        gstats[stats['podIp']] =  stats

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    runner = aiohttp.web.AppRunner(app)
    loop.run_until_complete(runner.setup())
    site = aiohttp.web.TCPSite(runner, port=8888)
    loop.run_until_complete(site.start())

    listen = loop.create_datagram_endpoint(StatsListener
                            , local_addr=('0.0.0.0', 7000))
    loop.run_until_complete(listen)

    loop.run_forever()

    # web.run_app(app, port=8888)
