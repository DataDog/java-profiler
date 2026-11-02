---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:00:25 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 9 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793631310 48
1793631315 48
1793631320 48
1793631325 48
1793631330 48
1793631335 48
1793631340 48
1793631345 48
1793631350 48
1793631355 48
1793631360 48
1793631365 48
1793631370 48
1793631375 48
1793631380 36
1793631385 36
1793631390 36
1793631395 36
1793631400 36
1793631405 36
```
</details>

---

