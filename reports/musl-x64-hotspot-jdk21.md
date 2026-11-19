---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:10:56 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 67-76 cores)</summary>

```
1795107954 71
1795107959 71
1795107964 71
1795107969 71
1795107974 71
1795107979 71
1795107984 76
1795107989 76
1795107994 76
1795107999 76
1795108004 76
1795108009 76
1795108014 76
1795108019 76
1795108024 76
1795108029 76
1795108035 76
1795108040 76
1795108045 76
1795108050 76
```
</details>

---

