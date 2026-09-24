---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 10 |
| Allocations | 419 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1790238278 50
1790238283 50
1790238288 50
1790238293 50
1790238298 50
1790238303 50
1790238308 50
1790238313 50
1790238318 50
1790238323 50
1790238328 50
1790238333 50
1790238338 50
1790238343 50
1790238348 50
1790238353 50
1790238358 50
1790238363 64
1790238368 64
1790238373 64
```
</details>

---

