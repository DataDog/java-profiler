---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:56:25 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 39-45 cores)</summary>

```
1795186303 39
1795186308 39
1795186313 39
1795186318 45
1795186323 45
1795186328 42
1795186333 42
1795186338 42
1795186343 42
1795186348 42
1795186353 42
1795186358 42
1795186363 42
1795186368 42
1795186373 42
1795186378 45
1795186383 45
1795186388 45
1795186393 45
1795186398 43
```
</details>

---

