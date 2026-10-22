---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (5 unique values: 39-48 cores)</summary>

```
1792676367 39
1792676372 39
1792676377 39
1792676382 41
1792676387 41
1792676392 41
1792676397 41
1792676402 43
1792676407 43
1792676412 43
1792676417 43
1792676422 48
1792676427 48
1792676432 48
1792676437 48
1792676442 48
1792676447 48
1792676452 48
1792676457 48
1792676462 48
```
</details>

---

