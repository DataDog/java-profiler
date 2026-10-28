---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 05:04:14 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (6 unique values: 36-46 cores)</summary>

```
1793177971 41
1793177976 41
1793177981 41
1793177986 41
1793177991 42
1793177996 42
1793178001 44
1793178006 44
1793178011 44
1793178016 44
1793178021 44
1793178026 44
1793178031 44
1793178036 44
1793178041 44
1793178046 44
1793178051 44
1793178056 46
1793178061 46
1793178066 39
```
</details>

---

