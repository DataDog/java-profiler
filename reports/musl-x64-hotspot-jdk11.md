---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 03:44:17 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (2 unique values: 57-74 cores)</summary>

```
1794299954 74
1794299959 74
1794299964 74
1794299969 74
1794299974 74
1794299979 57
1794299984 57
1794299989 57
1794299994 57
1794299999 57
1794300004 57
1794300009 57
1794300014 57
1794300019 57
1794300024 57
1794300029 57
1794300034 57
1794300039 57
1794300044 57
1794300049 57
```
</details>

---

