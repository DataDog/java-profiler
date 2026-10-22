---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 03:56:31 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 15 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1792655578 48
1792655583 48
1792655588 48
1792655593 48
1792655598 48
1792655603 48
1792655608 48
1792655613 43
1792655618 43
1792655623 43
1792655628 43
1792655633 43
1792655638 43
1792655643 43
1792655648 43
1792655653 38
1792655658 38
1792655663 33
1792655668 33
1792655673 38
```
</details>

---

