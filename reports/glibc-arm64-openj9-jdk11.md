---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 10:37:16 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 13 |
| Allocations | 182 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786977230 44
1786977235 44
1786977240 44
1786977245 44
1786977250 48
1786977255 48
1786977260 48
1786977265 48
1786977270 43
1786977275 43
1786977280 43
1786977285 43
1786977290 43
1786977295 43
1786977300 43
1786977305 43
1786977310 43
1786977315 43
1786977320 43
1786977325 43
```
</details>

---

