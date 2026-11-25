---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:29:11 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795627404 42
1795627409 42
1795627414 47
1795627419 47
1795627424 47
1795627429 47
1795627435 47
1795627440 47
1795627445 47
1795627450 47
1795627455 47
1795627460 47
1795627465 47
1795627470 47
1795627475 47
1795627480 47
1795627485 47
1795627490 47
1795627495 47
1795627500 47
```
</details>

---

