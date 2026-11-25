---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:23:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 64-68 cores)</summary>

```
1795634321 67
1795634326 67
1795634331 68
1795634336 68
1795634341 68
1795634346 68
1795634351 66
1795634356 66
1795634361 66
1795634366 66
1795634371 66
1795634376 66
1795634381 66
1795634386 66
1795634391 64
1795634396 64
1795634401 64
1795634406 64
1795634412 64
1795634417 64
```
</details>

---

