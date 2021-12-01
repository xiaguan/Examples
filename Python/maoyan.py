import json
import re
import time

import requests

def get_one_page(url):
    headers = {
        'Cookies': '__mta=187079319.1631855136461.1638333391036.1638333395267.7; '
                   '_lxsdk_cuid=17bf2254e48c8-06c9a2f4693f12-a7d173c-1fa400-17bf2254e4846; '
                   '__mta=187079319.1631855136461.1631855151773.1631855157853.4; uuid_n_v=v1; '
                   'uuid=2636DAF0526011ECB1F255F3476A9D13CEDA26553CC946818FCCD8AD85C676AB; '
                   '_csrf=f404087f4d1d33fc90910d2c22f563bbc018009a91d1d0636e328750beb97fea; '
                   'Hm_lvt_703e94591e87be68cc8da0da7cbd0be2=1638333340; _lx_utm=utm_source=bing&utm_medium=organic; '
                   '_lxsdk=2636DAF0526011ECB1F255F3476A9D13CEDA26553CC946818FCCD8AD85C676AB; '
                   '__mta=187079319.1631855136461.1631855157853.1638333356507.5; '
                   'Hm_lpvt_703e94591e87be68cc8da0da7cbd0be2=1638333395; _lxsdk_s=17d7446daa8-8ba-ad9-f21||15',
        'User-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                      'Chrome/96.0.4664.55 Safari/537.36 Edg/96.0.1054.34'
    }
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        print("nice!"+url)
        return response.text
    else:
        print("error")
        return None

def write_to_file(content):
    with open('temp.txt','a',encoding='utf-8') as f:
        f.write(json.dumps(content,ensure_ascii=False)+'\n')

def parse_one_page(html):
    pattern = re.compile(
        r"<i.*?board-index-(\d*).*?title=\"(\w*)?\".*?data-src=\"(.*?)\".*?主演：(.*?)</p>.*?time\">上映时间：(.*?)</p>.*?integer\">(\d).*?(\d)</i></p>",re.S)
    items = pattern.findall(html)
    print(items)
    for item in items:
        yield {
            'rank':item[0],
            'title':item[1],
            'img-src':item[2],
            'stars':item[3],
            'time':item[4],
            'score':str(item[5])+'.'+str(item[6])
        }

def main():
    for i in range(10):
        time.sleep(1)
        html = get_one_page('http://maoyan.com/board/4?offset=' + str(i*10))
        for item in parse_one_page(html):
            print(item)
            write_to_file(item)
main()
