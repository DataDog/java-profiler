---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:26:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 11 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 28-59 cores)</summary>

```
1795702943 28
1795702948 28
1795702953 28
1795702958 28
1795702963 28
1795702968 28
1795702973 28
1795702978 28
1795702983 28
1795702988 28
1795702993 28
1795702998 28
1795703003 28
1795703008 28
1795703013 28
1795703018 59
1795703023 59
1795703028 59
1795703033 59
1795703038 59
```
</details>

---

