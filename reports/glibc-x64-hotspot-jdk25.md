---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 01:03:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 51-84 cores)</summary>

```
1791435501 53
1791435506 53
1791435511 55
1791435516 55
1791435521 51
1791435526 51
1791435531 51
1791435536 51
1791435541 51
1791435546 51
1791435551 51
1791435556 51
1791435561 51
1791435566 51
1791435571 51
1791435576 84
1791435581 84
1791435586 84
1791435591 84
1791435596 84
```
</details>

---

