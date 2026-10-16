---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 04:44:28 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 6-18 cores)</summary>

```
1792139968 6
1792139973 6
1792139978 6
1792139983 6
1792139988 6
1792139993 6
1792139998 6
1792140003 6
1792140008 6
1792140013 6
1792140018 6
1792140023 6
1792140029 6
1792140034 6
1792140039 6
1792140044 18
1792140049 18
1792140054 18
1792140059 18
1792140064 18
```
</details>

---

