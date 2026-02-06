---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-06 09:56:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 53-67 cores)</summary>

```
1770389548 53
1770389553 53
1770389558 53
1770389563 53
1770389568 58
1770389573 58
1770389578 55
1770389583 55
1770389588 67
1770389593 67
1770389598 67
1770389603 67
1770389608 67
1770389613 67
1770389618 67
1770389623 67
1770389628 67
1770389633 61
1770389638 61
1770389643 61
```
</details>

---

