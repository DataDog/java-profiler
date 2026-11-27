---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:54:55 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795798278 47
1795798283 47
1795798288 47
1795798293 47
1795798298 47
1795798303 47
1795798308 47
1795798313 47
1795798318 47
1795798323 47
1795798328 47
1795798333 47
1795798338 47
1795798343 47
1795798348 47
1795798353 47
1795798358 47
1795798363 47
1795798368 47
1795798373 47
```
</details>

---

