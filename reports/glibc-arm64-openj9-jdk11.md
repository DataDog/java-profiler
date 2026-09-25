---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 09:02:24 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1111 |
| Sample Rate | 18.52/sec |
| Health Score | 1158% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790341029 48
1790341034 48
1790341039 48
1790341044 48
1790341049 48
1790341054 48
1790341059 48
1790341064 48
1790341069 48
1790341074 48
1790341079 48
1790341084 48
1790341089 48
1790341095 48
1790341100 48
1790341105 48
1790341110 48
1790341115 48
1790341120 48
1790341125 48
```
</details>

---

