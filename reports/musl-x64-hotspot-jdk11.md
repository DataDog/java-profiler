---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 09:45:34 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1787751597 69
1787751602 69
1787751607 69
1787751612 69
1787751617 71
1787751622 71
1787751627 71
1787751632 71
1787751637 71
1787751642 71
1787751647 71
1787751652 71
1787751657 71
1787751662 71
1787751667 71
1787751672 71
1787751677 71
1787751682 71
1787751687 71
1787751692 71
```
</details>

---

