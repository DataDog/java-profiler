---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:32:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 10 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 25-39 cores)</summary>

```
1794497299 39
1794497304 39
1794497309 39
1794497314 39
1794497319 39
1794497324 39
1794497329 39
1794497334 39
1794497339 39
1794497344 39
1794497349 39
1794497354 39
1794497359 39
1794497364 39
1794497369 39
1794497374 39
1794497379 39
1794497384 39
1794497389 39
1794497394 39
```
</details>

---

