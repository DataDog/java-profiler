---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 60-71 cores)</summary>

```
1791470845 66
1791470850 66
1791470855 66
1791470860 66
1791470865 66
1791470870 66
1791470875 66
1791470880 66
1791470885 66
1791470890 71
1791470895 71
1791470900 71
1791470905 71
1791470910 71
1791470915 71
1791470920 60
1791470925 60
1791470930 60
1791470935 60
1791470940 60
```
</details>

---

