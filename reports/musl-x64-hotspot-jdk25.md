---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 19:03:50 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 72-96 cores)</summary>

```
1794527944 72
1794527949 72
1794527954 72
1794527959 72
1794527964 72
1794527969 72
1794527974 72
1794527979 72
1794527984 72
1794527989 72
1794527994 72
1794527999 94
1794528005 94
1794528010 94
1794528015 94
1794528020 94
1794528025 94
1794528030 94
1794528035 94
1794528040 94
```
</details>

---

