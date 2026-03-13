---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:44:29 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 11 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 13 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1773394721 46
1773394726 46
1773394731 48
1773394736 48
1773394741 46
1773394746 46
1773394751 46
1773394756 46
1773394761 46
1773394766 46
1773394771 46
1773394776 46
1773394781 46
1773394786 46
1773394791 46
1773394796 46
1773394801 46
1773394806 46
1773394811 46
1773394816 46
```
</details>

---

