---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:44:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 82-87 cores)</summary>

```
1773394731 82
1773394736 82
1773394741 82
1773394746 82
1773394751 82
1773394756 82
1773394761 87
1773394766 87
1773394771 87
1773394776 87
1773394781 87
1773394786 87
1773394791 87
1773394796 87
1773394801 87
1773394806 87
1773394811 87
1773394816 87
1773394821 87
1773394826 87
```
</details>

---

