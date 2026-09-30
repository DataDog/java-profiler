---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 11:36:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1790782316 41
1790782321 39
1790782326 39
1790782331 39
1790782336 39
1790782341 39
1790782346 39
1790782351 39
1790782356 39
1790782361 39
1790782366 39
1790782371 39
1790782376 39
1790782381 39
1790782386 39
1790782391 39
1790782396 39
1790782401 48
1790782406 48
1790782411 48
```
</details>

---

