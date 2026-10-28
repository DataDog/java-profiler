---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:43:24 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1793187385 28
1793187390 28
1793187395 28
1793187400 28
1793187405 28
1793187410 28
1793187415 28
1793187420 28
1793187425 28
1793187430 30
1793187435 30
1793187440 30
1793187445 30
1793187450 28
1793187455 28
1793187460 28
1793187465 28
1793187470 30
1793187475 30
1793187480 30
```
</details>

---

