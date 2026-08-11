---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:28:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1786454461 77
1786454466 77
1786454471 77
1786454476 77
1786454481 79
1786454486 79
1786454491 79
1786454496 74
1786454501 74
1786454506 74
1786454511 74
1786454516 74
1786454521 74
1786454526 74
1786454531 74
1786454536 74
1786454541 74
1786454546 74
1786454551 74
1786454557 74
```
</details>

---

