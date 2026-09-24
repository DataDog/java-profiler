---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:29:12 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (6 unique values: 48-80 cores)</summary>

```
1790238314 50
1790238319 48
1790238324 48
1790238329 48
1790238334 48
1790238339 48
1790238344 58
1790238349 58
1790238354 58
1790238359 58
1790238364 58
1790238369 58
1790238374 60
1790238379 60
1790238384 60
1790238389 60
1790238394 70
1790238399 70
1790238404 80
1790238409 80
```
</details>

---

