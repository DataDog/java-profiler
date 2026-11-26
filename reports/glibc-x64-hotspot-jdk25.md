---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:25:29 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795706361 87
1795706366 87
1795706371 87
1795706376 85
1795706381 85
1795706386 85
1795706391 85
1795706396 85
1795706401 85
1795706406 85
1795706411 85
1795706416 85
1795706421 85
1795706426 85
1795706431 85
1795706436 85
1795706441 85
1795706446 85
1795706451 85
1795706456 85
```
</details>

---

