---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 01:05:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792558779 48
1792558784 48
1792558789 48
1792558794 48
1792558799 48
1792558804 48
1792558809 48
1792558814 48
1792558819 48
1792558824 48
1792558829 48
1792558834 48
1792558839 48
1792558844 48
1792558849 48
1792558854 48
1792558859 48
1792558864 48
1792558869 48
1792558874 48
```
</details>

---

