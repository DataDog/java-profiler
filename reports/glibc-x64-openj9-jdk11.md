---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:59:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1794311739 92
1794311744 92
1794311749 92
1794311754 92
1794311759 92
1794311764 92
1794311769 92
1794311774 92
1794311779 92
1794311784 92
1794311789 92
1794311794 92
1794311799 90
1794311804 90
1794311809 90
1794311814 90
1794311819 90
1794311824 90
1794311829 90
1794311834 90
```
</details>

---

