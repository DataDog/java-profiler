---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 12:43:57 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1793291943 44
1793291948 44
1793291953 44
1793291958 44
1793291963 44
1793291968 44
1793291973 44
1793291978 44
1793291983 44
1793291988 44
1793291993 44
1793291998 44
1793292003 44
1793292008 44
1793292013 44
1793292018 44
1793292023 44
1793292028 44
1793292033 44
1793292038 44
```
</details>

---

