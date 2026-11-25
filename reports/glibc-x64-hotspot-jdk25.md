---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 38-57 cores)</summary>

```
1795634329 55
1795634334 55
1795634339 55
1795634344 57
1795634349 57
1795634354 57
1795634359 57
1795634364 38
1795634369 38
1795634374 38
1795634379 38
1795634384 38
1795634389 38
1795634394 38
1795634399 38
1795634404 38
1795634409 38
1795634414 38
1795634419 38
1795634424 38
```
</details>

---

