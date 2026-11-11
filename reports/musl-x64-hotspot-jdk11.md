---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 12:34:06 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
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
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (5 unique values: 84-91 cores)</summary>

```
1794418074 91
1794418079 87
1794418084 87
1794418089 87
1794418094 87
1794418099 87
1794418104 87
1794418109 87
1794418114 84
1794418119 84
1794418124 84
1794418129 84
1794418134 84
1794418139 84
1794418144 84
1794418149 86
1794418154 86
1794418159 91
1794418164 91
1794418169 91
```
</details>

---

