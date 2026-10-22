---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 06:46:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 38-73 cores)</summary>

```
1792665774 71
1792665779 71
1792665784 73
1792665789 73
1792665794 73
1792665799 73
1792665804 73
1792665809 73
1792665814 38
1792665819 38
1792665824 38
1792665829 38
1792665834 38
1792665839 38
1792665844 38
1792665849 38
1792665854 38
1792665859 38
1792665864 38
1792665869 38
```
</details>

---

