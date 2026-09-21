---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1789995743 32
1789995748 32
1789995753 12
1789995758 12
1789995763 12
1789995769 12
1789995774 12
1789995779 12
1789995784 12
1789995789 12
1789995794 12
1789995799 12
1789995804 12
1789995809 12
1789995814 12
1789995819 12
1789995824 12
1789995829 12
1789995834 12
1789995839 12
```
</details>

---

