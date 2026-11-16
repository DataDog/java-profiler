---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:37:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 10 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794839674 51
1794839679 51
1794839684 51
1794839689 51
1794839694 51
1794839699 51
1794839704 39
1794839709 39
1794839714 39
1794839719 39
1794839724 39
1794839729 39
1794839734 39
1794839739 39
1794839744 39
1794839749 39
1794839754 39
1794839759 39
1794839764 39
1794839769 39
```
</details>

---

