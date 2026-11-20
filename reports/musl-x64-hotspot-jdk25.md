---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:56:26 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (5 unique values: 71-94 cores)</summary>

```
1795186305 94
1795186310 87
1795186315 87
1795186320 83
1795186325 83
1795186330 83
1795186335 83
1795186340 83
1795186346 83
1795186351 83
1795186356 83
1795186361 83
1795186366 83
1795186371 83
1795186376 71
1795186381 71
1795186386 71
1795186391 71
1795186396 71
1795186401 71
```
</details>

---

