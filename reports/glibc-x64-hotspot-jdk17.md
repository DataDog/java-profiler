---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:21:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 56-94 cores)</summary>

```
1795641304 56
1795641309 56
1795641314 71
1795641319 71
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
```
</details>

---

