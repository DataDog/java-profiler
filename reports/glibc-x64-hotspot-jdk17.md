---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-06 06:33:10 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770377282 30
1770377287 30
1770377292 30
1770377297 30
1770377302 30
1770377307 30
1770377312 30
1770377317 30
1770377322 30
1770377327 32
1770377332 32
1770377337 32
1770377342 32
1770377347 32
1770377352 32
1770377357 32
1770377362 32
1770377367 32
1770377372 32
1770377377 32
```
</details>

---

