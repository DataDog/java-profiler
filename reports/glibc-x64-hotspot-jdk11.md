---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1795098314 89
1795098319 89
1795098324 89
1795098329 89
1795098334 89
1795098339 89
1795098344 89
1795098349 89
1795098354 89
1795098359 89
1795098364 89
1795098369 89
1795098374 91
1795098379 91
1795098384 91
1795098389 91
1795098394 91
1795098399 91
1795098404 91
1795098409 96
```
</details>

---

