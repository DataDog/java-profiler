---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-12 04:38:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1786523569 34
1786523574 34
1786523579 34
1786523584 34
1786523589 34
1786523594 34
1786523599 14
1786523604 14
1786523609 14
1786523614 14
1786523619 14
1786523624 14
1786523629 14
1786523634 14
1786523639 14
1786523644 14
1786523649 14
1786523654 14
1786523659 14
1786523664 14
```
</details>

---

