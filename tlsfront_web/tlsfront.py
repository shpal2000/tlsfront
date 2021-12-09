import os
import aiohttp, json
from aiohttp import web
import asyncio
import json

gstats = {}
stats_ticks = 60

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
        appId = stats['appId']
        podIp = stats['podIp']
        del stats['appId']
        del stats['podIp']

        if not gstats.get(appId):
            gstats[appId] = {}
        if not gstats[appId].get(podIp):
            gstats[appId][podIp] = []

        gstats[appId][podIp].append(stats)
        if len(gstats[appId][podIp]) > stats_ticks:
            gstats[appId][podIp].pop(0)


        if gstats[appId].get('sum'):
            del gstats[appId]['sum']

        last_stats = []
        sum_stats = {}
        for _, v in gstats[appId].items():
            if v:
                last_stats.append(v[len(v)-1])

        if last_stats:
            for k, _ in stats.items():
                sum_stats[k] = 0
                for next_stats in last_stats:
                    sum_stats[k] = sum_stats[k]+next_stats[k]

        gstats[appId]['sum'] = sum_stats

def main ():
    global stats_tick

    cfg_file = '/configs/config.json'
    with open(cfg_file) as f:
        cfg = json.loads(f.read())

    stats_ticks = cfg['stats_ticks']

    loop = asyncio.get_event_loop()
    runner = aiohttp.web.AppRunner(app)
    loop.run_until_complete(runner.setup())
    site = aiohttp.web.TCPSite(runner
                , host=cfg['webui_ip']
                , port=cfg['webui_port'])
    loop.run_until_complete(site.start())

    listen = loop.create_datagram_endpoint(StatsListener
                    , local_addr=(cfg['webui_ip']
                    , cfg['stats_port']))

    loop.run_until_complete(listen)

    loop.run_forever()
    # web.run_app(app, port=8888)

if __name__ == '__main__':
    main()
    
