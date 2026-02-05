---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-05 05:23:33 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1770286721 40
1770286726 40
1770286731 40
1770286736 40
1770286741 40
1770286746 40
1770286751 40
1770286756 40
1770286761 40
1770286766 40
1770286771 38
1770286776 38
1770286781 38
1770286786 38
1770286791 38
1770286796 38
1770286801 38
1770286806 38
1770286811 38
1770286816 38
```
</details>

---

