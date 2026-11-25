---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:19:51 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 71-94 cores)</summary>

```
1795641324 71
1795641329 71
1795641334 92
1795641339 92
1795641344 92
1795641349 92
1795641354 92
1795641359 92
1795641364 92
1795641369 94
1795641374 94
1795641379 94
1795641384 94
1795641389 94
1795641394 94
1795641399 94
1795641404 94
1795641409 94
1795641414 94
1795641419 94
```
</details>

---

