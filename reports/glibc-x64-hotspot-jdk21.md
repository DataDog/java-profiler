---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-01 09:14:16 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777641094 64
1777641099 64
1777641104 64
1777641109 64
1777641114 64
1777641119 64
1777641124 64
1777641129 64
1777641134 64
1777641139 64
1777641144 64
1777641149 64
1777641154 64
1777641159 64
1777641164 64
1777641169 64
1777641174 64
1777641179 64
1777641184 64
1777641189 59
```
</details>

---

