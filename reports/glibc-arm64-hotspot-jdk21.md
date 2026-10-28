---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:27:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1793204596 43
1793204601 43
1793204606 43
1793204611 43
1793204616 43
1793204621 43
1793204626 43
1793204631 43
1793204636 45
1793204641 45
1793204646 45
1793204651 45
1793204656 48
1793204661 48
1793204666 48
1793204671 48
1793204676 48
1793204681 48
1793204686 43
1793204691 43
```
</details>

---

