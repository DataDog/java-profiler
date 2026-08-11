---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-31 cores)</summary>

```
1786454466 31
1786454471 31
1786454476 31
1786454481 31
1786454486 31
1786454491 31
1786454496 31
1786454501 31
1786454506 31
1786454511 31
1786454516 31
1786454521 31
1786454526 31
1786454531 31
1786454536 31
1786454541 31
1786454546 30
1786454551 30
1786454556 30
1786454561 30
```
</details>

---

