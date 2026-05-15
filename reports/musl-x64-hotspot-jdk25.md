---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-15 08:44:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 18-30 cores)</summary>

```
1778848651 30
1778848656 30
1778848661 30
1778848666 30
1778848671 30
1778848676 30
1778848681 30
1778848686 30
1778848691 30
1778848696 27
1778848701 27
1778848706 22
1778848711 22
1778848716 22
1778848721 22
1778848726 22
1778848731 22
1778848736 18
1778848741 18
1778848746 18
```
</details>

---

