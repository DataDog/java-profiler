---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 09:53:39 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795618018 47
1795618023 47
1795618028 47
1795618033 64
1795618038 64
1795618043 64
1795618048 64
1795618053 64
1795618058 64
1795618063 64
1795618068 64
1795618073 44
1795618078 44
1795618083 44
1795618088 44
1795618093 44
1795618098 44
1795618103 44
1795618108 44
1795618113 44
```
</details>

---

