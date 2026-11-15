---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 08:56:20 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 27-74 cores)</summary>

```
1794750729 27
1794750734 27
1794750739 27
1794750744 27
1794750749 27
1794750754 29
1794750759 29
1794750764 29
1794750769 29
1794750774 29
1794750779 29
1794750784 29
1794750789 29
1794750794 29
1794750799 29
1794750804 29
1794750809 29
1794750814 27
1794750819 27
1794750824 74
```
</details>

---

