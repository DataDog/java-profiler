---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ❌ FAIL

**Date:** 2026-01-27 11:39:15 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 8 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 22 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769531774 24
1769531779 24
1769531784 24
1769531789 24
1769531794 24
1769531799 24
1769531804 24
1769531809 24
1769531814 24
1769531819 24
1769531824 24
1769531829 24
1769531834 24
1769531839 24
1769531844 24
1769531849 24
1769531854 24
1769531859 24
1769531864 24
1769531869 24
```
</details>

---

