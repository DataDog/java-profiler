---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 14:23:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 70-92 cores)</summary>

```
1795634317 92
1795634322 92
1795634327 92
1795634332 70
1795634337 70
1795634342 70
1795634347 70
1795634352 70
1795634357 70
1795634362 70
1795634367 70
1795634372 70
1795634377 70
1795634382 70
1795634387 70
1795634392 72
1795634397 72
1795634402 72
1795634407 72
1795634412 72
```
</details>

---

