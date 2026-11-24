---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 07:51:05 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 30-34 cores)</summary>

```
1795524374 30
1795524379 30
1795524384 34
1795524389 34
1795524394 34
1795524399 34
1795524404 34
1795524409 34
1795524414 34
1795524419 34
1795524424 34
1795524429 34
1795524434 34
1795524439 34
1795524444 34
1795524449 34
1795524454 34
1795524459 34
1795524464 34
1795524469 34
```
</details>

---

