#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Fake `gh api` for test_babysit_pr.py. Routes live in $FAKE_GH_DIR/routes.json as
{"METHOD path": response}; the query string is ignored. Every call is appended to
calls.jsonl. fail.json maps a route to [stderr, count]: its next count calls fail.
Unrouted writes answer {"id": <n>}; unrouted reads fail with HTTP 404."""

import json
import os
import sys

d = os.environ["FAKE_GH_DIR"]
args = sys.argv[1:]
assert args[0] == "api", args
method = args[args.index("-X") + 1]
path = [a for a in args[1:] if a.startswith("repos/") or a == "user"][0].split("?")[0]
jq = args[args.index("--jq") + 1] if "--jq" in args else None
body = json.loads(sys.stdin.read()) if "--input" in args else None
key = "%s %s" % (method, path)
with open(os.path.join(d, "calls.jsonl"), "a") as f:
    f.write(json.dumps({"key": key, "body": body}) + "\n")


def load(name, default):
    try:
        with open(os.path.join(d, name)) as f:
            return json.load(f)
    except FileNotFoundError:
        return default


fail = load("fail.json", {})
if fail.get(key, [None, 0])[1] > 0:
    fail[key][1] -= 1
    with open(os.path.join(d, "fail.json"), "w") as f:
        json.dump(fail, f)
    sys.stderr.write(fail[key][0] + "\n")
    sys.exit(1)
routes = load("routes.json", {})
if key not in routes:
    if method == "GET":
        sys.stderr.write("gh: Not Found (HTTP 404)\n")
        sys.exit(1)
    n = len(open(os.path.join(d, "calls.jsonl")).read().splitlines())
    print(json.dumps({"id": 900000 + n}))
    sys.exit(0)
resp = routes[key]
if jq:
    items = resp.get(jq[1:-2]) if jq != ".[]" else resp
    for item in items:
        print(json.dumps(item))
else:
    print(json.dumps(resp))
