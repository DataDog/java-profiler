---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 50-60 cores)</summary>

```
1770135199 60
1770135204 60
1770135209 58
1770135214 58
1770135219 58
1770135224 58
1770135229 58
1770135234 58
1770135239 60
1770135244 60
1770135249 60
1770135254 60
1770135259 60
1770135264 60
1770135269 60
1770135274 60
1770135279 52
1770135284 52
1770135289 52
1770135294 52
```
</details>

---

