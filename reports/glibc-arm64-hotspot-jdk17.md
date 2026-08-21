---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-21 19:10:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 9 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1787353578 36
1787353583 36
1787353588 36
1787353593 36
1787353598 36
1787353603 36
1787353608 48
1787353613 48
1787353618 48
1787353623 48
1787353628 48
1787353633 48
1787353638 43
1787353643 43
1787353648 43
1787353653 43
1787353658 43
1787353663 43
1787353668 43
1787353673 43
```
</details>

---

