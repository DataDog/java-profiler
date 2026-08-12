---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:47:59 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 41-51 cores)</summary>

```
1786527848 51
1786527853 51
1786527858 51
1786527863 41
1786527868 41
1786527873 41
1786527878 41
1786527883 41
1786527888 41
1786527893 41
1786527898 41
1786527904 41
1786527909 41
1786527914 41
1786527919 41
1786527924 41
1786527929 41
1786527934 41
1786527939 41
1786527944 41
```
</details>

---

