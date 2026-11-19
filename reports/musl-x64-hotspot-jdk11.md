---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:48:44 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 12 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1795095855 38
1795095860 38
1795095865 38
1795095870 38
1795095875 38
1795095880 38
1795095885 38
1795095890 38
1795095895 38
1795095900 38
1795095905 36
1795095910 36
1795095915 36
1795095920 36
1795095925 36
1795095930 36
1795095935 38
1795095940 38
1795095945 38
1795095950 38
```
</details>

---

