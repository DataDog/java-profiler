---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1789995766 46
1789995771 46
1789995776 46
1789995781 46
1789995786 46
1789995791 46
1789995796 46
1789995801 46
1789995806 46
1789995811 46
1789995816 46
1789995821 46
1789995826 46
1789995831 46
1789995836 46
1789995841 46
1789995846 46
1789995851 44
1789995856 44
1789995861 44
```
</details>

---

