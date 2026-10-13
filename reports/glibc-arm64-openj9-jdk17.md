---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 12:35:44 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 8-10 cores)</summary>

```
1791908951 10
1791908956 10
1791908961 10
1791908966 10
1791908971 10
1791908976 10
1791908981 10
1791908986 8
1791908991 8
1791908996 8
1791909001 8
1791909006 8
1791909011 8
1791909016 8
1791909021 8
1791909026 8
1791909031 8
1791909036 8
1791909041 8
1791909046 8
```
</details>

---

