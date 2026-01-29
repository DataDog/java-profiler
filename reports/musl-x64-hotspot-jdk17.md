---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 24.70/sec |
| Health Score | 1544% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (5 unique values: 62-73 cores)</summary>

```
1769697751 73
1769697756 73
1769697761 71
1769697766 71
1769697771 71
1769697776 66
1769697781 66
1769697786 66
1769697791 66
1769697796 66
1769697801 66
1769697806 66
1769697811 66
1769697816 66
1769697821 66
1769697826 66
1769697831 66
1769697836 66
1769697841 66
1769697846 66
```
</details>

---

