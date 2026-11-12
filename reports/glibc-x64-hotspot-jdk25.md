---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:32:59 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 82-87 cores)</summary>

```
1794497264 82
1794497269 82
1794497274 82
1794497279 82
1794497284 84
1794497289 84
1794497294 84
1794497299 84
1794497304 86
1794497309 86
1794497314 86
1794497319 86
1794497324 86
1794497329 86
1794497334 86
1794497339 86
1794497344 86
1794497349 86
1794497354 86
1794497359 86
```
</details>

---

