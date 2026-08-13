---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 16:15:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786651900 32
1786651905 32
1786651910 32
1786651915 32
1786651920 32
1786651925 32
1786651930 32
1786651935 32
1786651940 32
1786651945 32
1786651950 32
1786651955 30
1786651960 30
1786651965 30
1786651970 30
1786651975 30
1786651980 30
1786651985 30
1786651990 30
1786651995 30
```
</details>

---

