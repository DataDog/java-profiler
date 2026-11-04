---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 20:28:23 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 570 |

<details>
<summary>CPU Timeline (2 unique values: 35-55 cores)</summary>

```
1793755424 35
1793755429 35
1793755434 35
1793755439 35
1793755444 35
1793755449 35
1793755454 35
1793755459 55
1793755464 55
1793755469 55
1793755474 55
1793755479 55
1793755484 55
1793755489 55
1793755494 55
1793755499 55
1793755504 55
1793755509 55
1793755514 55
1793755519 55
```
</details>

---

