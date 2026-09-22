---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:11 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (5 unique values: 33-64 cores)</summary>

```
1790074869 64
1790074874 64
1790074879 64
1790074884 64
1790074889 64
1790074894 64
1790074899 64
1790074904 64
1790074910 64
1790074915 43
1790074920 43
1790074925 43
1790074930 43
1790074935 41
1790074940 41
1790074945 41
1790074950 41
1790074955 41
1790074960 41
1790074965 41
```
</details>

---

