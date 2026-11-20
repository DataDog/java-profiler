---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:39:02 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 31-45 cores)</summary>

```
1795170950 36
1795170955 36
1795170960 36
1795170965 36
1795170970 36
1795170975 36
1795170980 36
1795170985 36
1795170990 31
1795170995 31
1795171000 31
1795171005 31
1795171010 31
1795171015 31
1795171020 45
1795171025 45
1795171030 45
1795171035 45
1795171040 45
1795171045 45
```
</details>

---

