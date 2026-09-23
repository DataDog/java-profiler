---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:52:01 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 11-48 cores)</summary>

```
1790174773 11
1790174778 11
1790174783 11
1790174788 11
1790174793 11
1790174798 11
1790174803 11
1790174809 11
1790174814 11
1790174819 11
1790174824 11
1790174829 48
1790174834 48
1790174839 48
1790174844 48
1790174849 48
1790174854 48
1790174859 48
1790174864 48
1790174869 48
```
</details>

---

