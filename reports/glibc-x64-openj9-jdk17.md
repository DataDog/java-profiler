---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 08:56:20 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 10 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794750689 79
1794750694 79
1794750699 79
1794750704 79
1794750709 79
1794750714 81
1794750719 81
1794750724 81
1794750729 81
1794750734 81
1794750739 81
1794750744 81
1794750749 81
1794750754 81
1794750759 81
1794750764 81
1794750769 81
1794750774 81
1794750779 81
1794750784 81
```
</details>

---

