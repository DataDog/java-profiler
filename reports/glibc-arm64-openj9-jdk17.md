---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:38:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786523574 46
1786523579 46
1786523584 46
1786523589 46
1786523594 48
1786523599 48
1786523604 48
1786523609 48
1786523614 48
1786523619 48
1786523624 48
1786523629 48
1786523634 48
1786523639 48
1786523644 48
1786523649 48
1786523654 48
1786523659 48
1786523664 43
1786523669 43
```
</details>

---

