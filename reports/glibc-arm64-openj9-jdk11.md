---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 14:12:55 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790618938 48
1790618943 48
1790618948 48
1790618953 48
1790618958 48
1790618963 48
1790618968 48
1790618973 48
1790618978 48
1790618983 48
1790618988 48
1790618993 48
1790618998 48
1790619003 48
1790619008 48
1790619013 48
1790619018 48
1790619023 48
1790619028 48
1790619033 48
```
</details>

---

