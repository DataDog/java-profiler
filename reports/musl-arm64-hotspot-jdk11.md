---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 05:47:57 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795344222 24
1795344227 24
1795344232 24
1795344237 24
1795344242 24
1795344247 24
1795344252 24
1795344257 24
1795344262 24
1795344267 29
1795344272 29
1795344277 29
1795344282 29
1795344287 29
1795344292 29
1795344297 29
1795344302 29
1795344307 29
1795344312 29
1795344317 29
```
</details>

---

