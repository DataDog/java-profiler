---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:28:36 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 35 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (5 unique values: 61-68 cores)</summary>

```
1795706706 61
1795706711 61
1795706716 61
1795706721 63
1795706726 63
1795706731 63
1795706736 63
1795706741 65
1795706746 65
1795706751 65
1795706756 68
1795706761 68
1795706766 68
1795706771 68
1795706776 68
1795706781 68
1795706786 68
1795706791 68
1795706796 66
1795706801 66
```
</details>

---

