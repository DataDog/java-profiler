---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:44:47 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 8 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788363461 64
1788363466 59
1788363471 59
1788363476 59
1788363481 59
1788363486 59
1788363491 59
1788363496 59
1788363501 59
1788363506 59
1788363511 59
1788363516 64
1788363521 64
1788363526 64
1788363531 64
1788363536 64
1788363541 64
1788363546 64
1788363551 64
1788363556 64
```
</details>

---

