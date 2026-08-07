---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 10:30:55 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 12 |
| Allocations | 228 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1786112743 39
1786112748 39
1786112753 39
1786112758 39
1786112763 39
1786112768 39
1786112773 34
1786112778 34
1786112783 34
1786112788 34
1786112794 34
1786112799 34
1786112804 34
1786112809 34
1786112814 34
1786112819 34
1786112824 34
1786112829 39
1786112834 39
1786112839 39
```
</details>

---

