---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 07:23:43 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1790853535 11
1790853540 32
1790853545 32
1790853550 32
1790853555 32
1790853560 32
1790853565 32
1790853570 32
1790853575 32
1790853580 10
1790853585 10
1790853590 10
1790853595 10
1790853600 10
1790853605 10
1790853610 10
1790853615 10
1790853620 10
1790853625 10
1790853630 10
```
</details>

---

