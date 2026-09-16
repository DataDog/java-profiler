---
id: ev-toolkit-and-onpod-methodology
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-onpod-evidence-methodology, dead-jcmd-jfr-dump-wrong-source, dead-toolkit-prod-datacenter]
tags: [methodology, user-quote, profiling-toolkit, tooling-gotcha]
created: 2026-08-24
updated: 2026-08-24
---

# Methodology corrections and tooling gotchas from this session

## User quote (verbatim)

> you should be able to read the pods from the pod

Context: the first conclusion had been assembled from Profiling Toolkit
downloads plus image-tag inference. The correction was to gather the
evidence on the pod itself — `kubectl exec` + `/usr/bin/jar xf` +
`md5sum` + `strings` — which is what produced
`ev-deployed-so-1481-no-symbols`.

Other verbatim user messages this session:

> use the jfr-analyzer and dd-triage skills to download hotdog profiles from
> prof-analyzer jb hotdog and check whether we are getting any reference
> chain events. if not, investigate the logs from the pod to see what is
> happening

> I resynced and reuploaded the agent. It SHOULD be there now

## Profiling Toolkit gotchas

Working invocation:

```
python3 ~/.claude/skills/profiling-toolkit-analyze/download.py \
  --org-id 2 --service prof-analyzer-hotdog --app prof-analyzer-hotdog-jb \
  --datacenter us1.staging.dog --from "20 minutes ago" --to "now" \
  --limit 5 --output-dir /tmp/hotdog-jb-fresh3
```

Failure modes hit before landing on that:

- `--datacenter us1.prod.dog` returns query hits but the blob download 404s:
  ```
  ERROR: Download failed: HTTP 404 - {"errors":[{"code":"ObjectNotFoundException"}]}
  Query: *
  Found 1 matching profiles
  ```
- Adding `--env staging` alongside `--service`/`--app` yielded
  `Found 0 matching profiles` even though profiles existed.
- Many results are `.tar` blobs containing only `cpu.pprof`
  ("no JFR found in tar"); only some entries are real `.jfr`.
- Pod env for reference: `DD_ENV=staging`, `DD_SERVICE=prof-analyzer-hotdog`,
  `DD_SERVICE_MAPPING=kafka:prof-analyzer-hotdog-jb`, `POD_NAME=` (empty).

## Other tooling notes

- jafar `jfr_open` on a 9.5 MB uploaded JFR exceeded the 120 s MCP timeout
  and had to be `TaskStop`ped (task `k1scf1c6f`); `strings | grep` on the
  raw file was the fast substitute for checking which event types exist.
- The pod has `/usr/bin/jar` but **no** `unzip` and no `python3`.
