---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-14 01:01:23 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1786683329 88
1786683334 88
1786683339 88
1786683344 88
1786683349 88
1786683354 88
1786683359 86
1786683364 86
1786683369 86
1786683374 86
1786683379 86
1786683384 86
1786683389 88
1786683394 88
1786683399 88
1786683404 88
1786683409 88
1786683414 88
1786683419 88
1786683424 96
```
</details>

---

