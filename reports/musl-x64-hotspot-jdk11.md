---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:38:15 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 63-87 cores)</summary>

```
1786523593 67
1786523598 67
1786523603 87
1786523608 87
1786523613 63
1786523618 63
1786523623 63
1786523628 63
1786523633 63
1786523638 63
1786523643 63
1786523648 63
1786523653 63
1786523658 63
1786523663 63
1786523668 63
1786523673 63
1786523678 63
1786523683 63
1786523688 63
```
</details>

---

