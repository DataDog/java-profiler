---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 05:53:14 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1787305726 92
1787305731 92
1787305736 92
1787305741 92
1787305746 92
1787305751 92
1787305756 92
1787305761 92
1787305766 92
1787305771 92
1787305776 92
1787305781 90
1787305786 90
1787305791 90
1787305796 90
1787305801 90
1787305806 90
1787305811 88
1787305816 88
1787305821 88
```
</details>

---

