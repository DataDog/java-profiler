---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:40:05 EST

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794324927 48
1794324932 48
1794324937 48
1794324942 48
1794324947 48
1794324952 48
1794324957 48
1794324962 48
1794324967 48
1794324972 48
1794324977 48
1794324982 48
1794324987 48
1794324992 48
1794324997 48
1794325002 48
1794325007 48
1794325012 48
1794325017 43
1794325022 43
```
</details>

---

