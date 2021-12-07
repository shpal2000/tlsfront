import os
import aiohttp, json
from aiohttp import web

async def index_handle(request):
    return web.FileResponse('public/index.html')

app = web.Application()

app.add_routes([web.static('/build', 'public/build')])
app.add_routes([web.static('/assets', 'public/assets')])
app.add_routes([web.route('get', '/{tail:.*}', index_handle)])

if __name__ == '__main__':  
    web.run_app(app, port=8888)

# app.add_routes([web.static('/assets', 'ui/assets')])
# app.add_routes([web.route('*', '/api/{api_path:.*}', api_handle)])
# app.add_routes([web.route('get', '/favicon.ico', favicon_handle)])
# app.add_routes([web.route('get', '/robots.txt', robots_handle)])
# app.add_routes([web.route('get', '/{tail:.*}', index_handle)])