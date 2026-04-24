---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:33:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1777033630 54
1777033635 59
1777033640 59
1777033645 59
1777033650 54
1777033655 54
1777033660 54
1777033665 54
1777033670 54
1777033675 54
1777033680 54
1777033685 54
1777033690 54
1777033695 54
1777033700 54
1777033705 54
1777033710 54
1777033715 54
1777033720 54
1777033725 54
```
</details>

---

