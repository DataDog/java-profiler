---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:39:48 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (6 unique values: 46-61 cores)</summary>

```
1778171730 49
1778171736 49
1778171741 49
1778171746 49
1778171751 54
1778171756 54
1778171761 46
1778171766 46
1778171771 46
1778171776 46
1778171781 46
1778171786 56
1778171791 56
1778171796 56
1778171801 56
1778171806 59
1778171811 59
1778171816 59
1778171821 59
1778171826 59
```
</details>

---

