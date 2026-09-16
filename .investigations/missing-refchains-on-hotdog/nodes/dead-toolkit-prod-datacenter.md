---
id: dead-toolkit-prod-datacenter
type: deadend
status: refuted
depends_on: [ev-toolkit-and-onpod-methodology]
supersedes: []
related: [dead-jcmd-jfr-dump-wrong-source, find-onpod-evidence-methodology]
tags: [profiling-toolkit, tooling-gotcha, datacenter, org-id]
created: 2026-08-24
updated: 2026-08-24
---

# Dead end: `--datacenter us1.prod.dog` for staging hotdog profiles

## Reasoning chain

`download.py` has no datacenter default and refuses to guess. The first
several attempts used `--org-id 2 --datacenter us1.prod.dog` and reported
`Found 0 matching profiles` for every service/app/query combination —
which briefly looked like "the pod isn't uploading at all".

Probing with no service filter disambiguated it:

```
=== no service filter, org 2, prod dc ===
  ERROR: Download failed: HTTP 404 - {"errors":[{"code":"ObjectNotFoundException"}]}
  Query: *
  Found 1 matching profiles
=== no service filter, org 2, staging dc ===
  Query: *
  Found 1 matching profiles
```

So `us1.prod.dog` can *find* profiles but 404s on blob download. The
working combination is org 2 + `--datacenter us1.staging.dog`, which then
returned 5 profiles for
`service:prof-analyzer-hotdog app:prof-analyzer-hotdog-jb`.

Secondary gotchas found along the way: adding `--env staging` alongside
`--service`/`--app` produced 0 hits even though matching profiles existed;
`--service` etc. must precede other args or argparse rejects them as
unrecognized; and a large share of results are `.tar` blobs containing
only `cpu.pprof` ("no JFR found in tar").

## Evidence
- `evidence/ev-toolkit-and-onpod-methodology.md`

## What this rules out
- Concluding "the pod isn't uploading profiles" from a toolkit
  `Found 0 matching profiles` result before verifying org-id and
  datacenter.
- Note this contradicts the previously recorded
  "profiling-toolkit needs the prod URL" rule for *staging pods* in this
  particular case: here the staging datacenter was required for the blob
  download to succeed.
