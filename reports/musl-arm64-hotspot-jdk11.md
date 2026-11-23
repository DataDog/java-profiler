---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:56:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795434746 48
1795434751 48
1795434756 48
1795434761 48
1795434766 48
1795434771 48
1795434776 48
1795434781 48
1795434786 48
1795434791 48
1795434796 48
1795434801 48
1795434806 48
1795434811 48
1795434816 48
1795434821 48
1795434826 48
1795434831 64
1795434836 64
1795434841 64
```
</details>

---

