---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 14:59:55 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 57-76 cores)</summary>

```
1793040909 71
1793040914 71
1793040919 71
1793040924 71
1793040929 71
1793040934 71
1793040939 71
1793040944 71
1793040949 71
1793040954 71
1793040959 76
1793040964 76
1793040969 76
1793040974 59
1793040979 59
1793040984 59
1793040989 59
1793040994 59
1793040999 59
1793041004 59
```
</details>

---

