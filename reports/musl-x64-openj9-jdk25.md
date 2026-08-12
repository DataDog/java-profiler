---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 04:38:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 27-36 cores)</summary>

```
1786523563 27
1786523568 27
1786523573 27
1786523578 27
1786523583 27
1786523588 27
1786523593 27
1786523598 27
1786523603 27
1786523608 27
1786523613 36
1786523618 36
1786523623 36
1786523629 36
1786523634 36
1786523639 36
1786523644 36
1786523649 36
1786523654 36
1786523659 36
```
</details>

---

