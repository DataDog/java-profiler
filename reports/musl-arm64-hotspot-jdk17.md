---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:48:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794930051 51
1794930056 51
1794930061 51
1794930066 51
1794930071 51
1794930076 51
1794930081 51
1794930086 51
1794930091 46
1794930096 46
1794930101 46
1794930106 46
1794930111 46
1794930116 41
1794930121 41
1794930126 41
1794930131 41
1794930136 41
1794930141 41
1794930146 41
```
</details>

---

