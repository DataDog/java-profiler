---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-02 14:43:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1788374367 24
1788374372 24
1788374377 24
1788374382 24
1788374387 24
1788374392 24
1788374397 24
1788374402 24
1788374407 24
1788374412 24
1788374417 22
1788374422 22
1788374427 22
1788374432 22
1788374437 22
1788374442 22
1788374447 22
1788374452 22
1788374457 22
1788374462 22
```
</details>

---

