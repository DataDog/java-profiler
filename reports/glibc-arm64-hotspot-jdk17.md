---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:53:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 10 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1794592159 51
1794592164 64
1794592169 64
1794592174 64
1794592179 64
1794592184 64
1794592189 64
1794592194 51
1794592199 51
1794592204 51
1794592209 51
1794592214 51
1794592219 51
1794592224 51
1794592229 51
1794592234 51
1794592239 51
1794592244 51
1794592249 51
1794592254 46
```
</details>

---

