---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 10:16:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1790604681 47
1790604686 47
1790604691 47
1790604696 47
1790604701 47
1790604706 47
1790604711 47
1790604716 47
1790604721 47
1790604726 47
1790604731 47
1790604736 45
1790604741 45
1790604746 43
1790604751 43
1790604756 43
1790604761 43
1790604766 43
1790604771 43
1790604776 43
```
</details>

---

