---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 44-65 cores)</summary>

```
1795084953 65
1795084958 65
1795084963 65
1795084968 65
1795084973 44
1795084978 44
1795084983 44
1795084988 44
1795084993 44
1795084998 44
1795085003 44
1795085008 44
1795085013 44
1795085018 44
1795085023 44
1795085028 44
1795085033 44
1795085038 44
1795085043 44
1795085048 44
```
</details>

---

