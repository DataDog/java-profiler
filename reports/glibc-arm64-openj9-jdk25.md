---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:56:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 36-40 cores)</summary>

```
1795171827 39
1795171832 39
1795171837 39
1795171842 39
1795171847 39
1795171852 39
1795171857 39
1795171862 39
1795171867 36
1795171872 36
1795171877 36
1795171882 36
1795171887 38
1795171892 38
1795171897 40
1795171902 40
1795171907 40
1795171912 40
1795171917 40
1795171922 40
```
</details>

---

