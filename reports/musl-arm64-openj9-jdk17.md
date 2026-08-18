---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 21:38:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1787016932 28
1787016937 28
1787016942 28
1787016947 28
1787016952 28
1787016957 28
1787016962 28
1787016967 23
1787016972 23
1787016977 23
1787016982 23
1787016987 23
1787016992 23
1787016997 23
1787017002 23
1787017007 23
1787017012 23
1787017017 23
1787017022 23
1787017027 23
```
</details>

---

