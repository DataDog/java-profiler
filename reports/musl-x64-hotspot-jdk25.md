---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 71-78 cores)</summary>

```
1795538263 78
1795538268 78
1795538273 78
1795538278 78
1795538283 78
1795538288 78
1795538293 78
1795538298 78
1795538303 78
1795538308 78
1795538313 78
1795538318 78
1795538323 78
1795538328 78
1795538333 78
1795538338 78
1795538343 71
1795538348 71
1795538353 71
1795538358 71
```
</details>

---

