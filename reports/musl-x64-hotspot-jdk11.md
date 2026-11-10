---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:42:55 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 51-72 cores)</summary>

```
1794324983 51
1794324988 51
1794324993 51
1794324998 51
1794325003 70
1794325008 70
1794325013 72
1794325018 72
1794325023 72
1794325028 72
1794325033 72
1794325038 72
1794325043 72
1794325048 72
1794325053 72
1794325059 72
1794325064 72
1794325069 72
1794325074 72
1794325079 72
```
</details>

---

