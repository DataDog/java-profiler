---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1792676387 44
1792676392 44
1792676397 44
1792676402 44
1792676407 44
1792676412 44
1792676417 44
1792676422 48
1792676427 48
1792676432 48
1792676437 48
1792676442 48
1792676447 48
1792676452 48
1792676457 48
1792676462 48
1792676467 48
1792676472 48
1792676477 48
1792676482 48
```
</details>

---

