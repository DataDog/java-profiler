---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:25:46 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1003 |
| Sample Rate | 16.72/sec |
| Health Score | 1045% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 69-74 cores)</summary>

```
1795015263 69
1795015268 69
1795015273 69
1795015278 69
1795015283 69
1795015288 69
1795015293 69
1795015298 74
1795015304 74
1795015309 74
1795015314 74
1795015319 74
1795015324 74
1795015329 74
1795015334 74
1795015339 74
1795015344 74
1795015349 74
1795015354 72
1795015359 72
```
</details>

---

