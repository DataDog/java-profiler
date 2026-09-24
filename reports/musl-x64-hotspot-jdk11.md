---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 44-96 cores)</summary>

```
1790238268 44
1790238273 44
1790238278 61
1790238283 61
1790238288 61
1790238293 61
1790238298 61
1790238303 61
1790238308 61
1790238313 61
1790238318 61
1790238323 61
1790238328 61
1790238333 61
1790238338 61
1790238343 84
1790238348 84
1790238353 84
1790238358 84
1790238363 96
```
</details>

---

