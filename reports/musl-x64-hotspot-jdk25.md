---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:03 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 46-53 cores)</summary>

```
1795382865 53
1795382870 53
1795382875 53
1795382880 53
1795382885 53
1795382890 53
1795382895 53
1795382900 53
1795382905 53
1795382910 53
1795382915 53
1795382920 53
1795382925 53
1795382930 53
1795382935 51
1795382940 51
1795382945 49
1795382950 49
1795382955 49
1795382960 51
```
</details>

---

