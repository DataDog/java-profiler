---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-07 12:39:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 65-82 cores)</summary>

```
1778171736 69
1778171741 69
1778171746 69
1778171751 65
1778171756 65
1778171761 65
1778171766 65
1778171771 65
1778171776 80
1778171781 80
1778171786 80
1778171791 82
1778171796 82
1778171801 82
1778171806 82
1778171811 82
1778171816 82
1778171821 82
1778171826 82
1778171831 82
```
</details>

---

