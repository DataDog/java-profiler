---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 10:37:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
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
1786977330 43
```
</details>

---

