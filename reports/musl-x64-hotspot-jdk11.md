---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 14:43:12 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 72-75 cores)</summary>

```
1777487766 75
1777487771 75
1777487776 75
1777487781 75
1777487786 75
1777487791 75
1777487796 75
1777487801 75
1777487806 75
1777487811 74
1777487816 74
1777487821 74
1777487826 74
1777487831 74
1777487836 74
1777487841 74
1777487846 74
1777487851 74
1777487856 72
1777487861 72
```
</details>

---

