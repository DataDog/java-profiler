---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:15 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1778158624 32
1778158629 32
1778158634 32
1778158639 31
1778158644 31
1778158649 31
1778158654 31
1778158659 31
1778158664 31
1778158669 31
1778158674 31
1778158679 32
1778158684 32
1778158689 32
1778158694 32
1778158699 32
1778158704 32
1778158709 32
1778158714 32
1778158719 32
```
</details>

---

