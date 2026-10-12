---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-12 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (5 unique values: 41-45 cores)</summary>

```
1791794232 44
1791794237 44
1791794242 44
1791794247 44
1791794252 45
1791794257 45
1791794262 45
1791794267 45
1791794272 45
1791794277 45
1791794282 43
1791794287 43
1791794292 42
1791794297 42
1791794302 42
1791794307 42
1791794312 42
1791794317 43
1791794322 43
1791794327 41
```
</details>

---

