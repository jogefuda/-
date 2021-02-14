import requests
import json
from datetime import datetime, timezone
import time

def utc_to_local(utc_dt):
    return utc_dt.replace(tzinfo=timezone.utc).astimezone(tz=None)

def id_in_range(_id: str, after: str, before: str):
    _id = int(_id)
    after = int(after)
    before = int(before)
    return after < _id < before

def main():
    appears = {}

    headers = {
        'Authorization': ''
    }

    channel_id = 0
    after  =  0
    before = 0

    while after < before:
        time.sleep(0.1) # rate limit 10,000 per 10 mins, sleep 16ms per request
        url = 'https://discord.com/api/v8/channels/{}/messages?after={}&limit=100'.format(channel_id, after)

        resp = requests.get(url, headers=headers)
        j = json.loads(resp.text)

        # if no more message return
        if len(j) == 0:
            break

        for msg in j:
            msg_id = msg['id']
            user_id = msg['author']['id']

            if not id_in_range(msg_id, after, before):
                continue

            username = msg['author']['username']
            content = msg['content']

            t = utc_to_local(datetime.fromisoformat(msg['timestamp']))
            t = t.isoformat().split('.')[0]
            print('[DEBUG] {} {}: {}'.format(t, username, content))

            if user_id in appears:
                appears[user_id][2] += 1
            else:
                appears.setdefault(user_id, [
                    user_id,
                    username,
                    1
                ])
        after = int(j[0]['id'])

    print('Done')
    for _, v in appears.items():
        print(v)

if __name__ == '__main__':
    main()
