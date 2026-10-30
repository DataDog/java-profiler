---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 17:09:24 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 13 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793394297 51
1793394302 51
1793394307 51
1793394312 51
1793394317 51
1793394322 51
1793394327 51
1793394332 51
1793394337 51
1793394342 51
1793394347 51
1793394352 51
1793394357 51
1793394362 51
1793394367 51
1793394372 51
1793394377 51
1793394382 51
1793394387 51
1793394392 51
```
</details>

---

