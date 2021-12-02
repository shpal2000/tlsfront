import os
import aiohttp, json
from aiohttp import web

async def index_handle(request):
    return web.FileResponse('public/index.html')

app = web.Application()

app.add_routes([web.static('/build', 'public/build')])
app.add_routes([web.route('get', '/{tail:.*}', index_handle)])


if __name__ == '__main__':  
    web.run_app(app, port=8888)
