---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-27 13:58:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1793123626 27
1793123631 27
1793123636 27
1793123641 27
1793123646 27
1793123651 27
1793123656 30
1793123661 30
1793123666 30
1793123671 30
1793123676 30
1793123681 30
1793123686 30
1793123691 30
1793123696 30
1793123701 30
1793123706 30
1793123711 30
1793123716 30
1793123721 30
```
</details>

---

