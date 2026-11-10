---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:40:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 322 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 46-63 cores)</summary>

```
1794324938 58
1794324943 58
1794324948 58
1794324953 58
1794324958 58
1794324963 58
1794324968 60
1794324973 60
1794324978 60
1794324983 60
1794324988 60
1794324993 60
1794324998 60
1794325003 60
1794325008 60
1794325013 60
1794325018 63
1794325023 63
1794325028 63
1794325033 63
```
</details>

---

