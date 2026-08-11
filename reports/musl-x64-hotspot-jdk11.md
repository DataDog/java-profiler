---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:28:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 47-68 cores)</summary>

```
1786454461 53
1786454466 53
1786454471 53
1786454476 53
1786454481 53
1786454486 53
1786454491 53
1786454496 53
1786454501 53
1786454506 47
1786454511 47
1786454516 47
1786454521 47
1786454526 47
1786454531 47
1786454536 47
1786454541 47
1786454546 47
1786454551 47
1786454556 47
```
</details>

---

