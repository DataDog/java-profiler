---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:47:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 48-49 cores)</summary>

```
1795426988 48
1795426993 48
1795426998 48
1795427003 48
1795427008 48
1795427013 48
1795427018 48
1795427023 48
1795427028 48
1795427033 48
1795427038 48
1795427043 48
1795427048 48
1795427053 49
1795427058 49
1795427063 49
1795427068 49
1795427073 49
1795427078 49
1795427083 49
```
</details>

---

