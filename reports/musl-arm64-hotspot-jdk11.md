---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 11:57:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1786463493 19
1786463498 24
1786463503 24
1786463508 24
1786463513 24
1786463518 24
1786463523 24
1786463528 24
1786463533 24
1786463538 24
1786463543 24
1786463548 24
1786463553 24
1786463558 24
1786463563 24
1786463568 24
1786463573 24
1786463579 24
1786463584 24
1786463589 24
```
</details>

---

