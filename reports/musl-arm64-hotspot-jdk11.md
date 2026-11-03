---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 13:50:10 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1793731434 36
1793731439 36
1793731444 36
1793731449 36
1793731454 36
1793731459 36
1793731464 36
1793731469 41
1793731474 41
1793731479 41
1793731484 41
1793731489 41
1793731494 41
1793731499 41
1793731504 41
1793731509 41
1793731514 41
1793731519 41
1793731524 41
1793731529 41
```
</details>

---

