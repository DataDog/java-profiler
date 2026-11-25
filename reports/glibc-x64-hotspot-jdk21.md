---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 47-75 cores)</summary>

```
1795641319 47
1795641324 47
1795641329 47
1795641334 47
1795641339 47
1795641344 47
1795641349 47
1795641354 47
1795641359 47
1795641364 47
1795641369 47
1795641374 47
1795641379 47
1795641384 47
1795641389 47
1795641394 49
1795641399 49
1795641404 49
1795641409 75
1795641414 75
```
</details>

---

