---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 23-48 cores)</summary>

```
1791470892 43
1791470897 43
1791470902 43
1791470907 48
1791470912 48
1791470917 48
1791470922 48
1791470927 48
1791470932 43
1791470937 43
1791470942 43
1791470947 43
1791470952 43
1791470957 43
1791470962 43
1791470967 43
1791470972 43
1791470977 43
1791470982 43
1791470987 43
```
</details>

---

