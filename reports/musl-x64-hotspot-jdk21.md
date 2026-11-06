---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 21:05:23 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 11 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 48-63 cores)</summary>

```
1793930461 63
1793930466 63
1793930471 63
1793930476 63
1793930481 63
1793930486 63
1793930491 48
1793930496 48
1793930501 48
1793930506 48
1793930511 48
1793930516 48
1793930521 48
1793930526 48
1793930531 48
1793930536 48
1793930541 48
1793930546 48
1793930551 48
1793930556 48
```
</details>

---

