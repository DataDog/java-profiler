---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 40-56 cores)</summary>

```
1789995756 56
1789995761 56
1789995766 56
1789995771 56
1789995776 56
1789995781 56
1789995786 56
1789995791 56
1789995796 56
1789995801 56
1789995806 56
1789995811 56
1789995816 56
1789995821 56
1789995826 56
1789995831 56
1789995836 56
1789995841 56
1789995846 48
1789995851 48
```
</details>

---

