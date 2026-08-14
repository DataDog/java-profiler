---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 01:01:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1786683324 64
1786683329 64
1786683334 64
1786683339 64
1786683344 64
1786683349 64
1786683354 64
1786683359 64
1786683364 64
1786683369 64
1786683374 64
1786683379 64
1786683384 62
1786683389 62
1786683394 62
1786683399 62
1786683404 62
1786683409 62
1786683414 62
1786683419 62
```
</details>

---

