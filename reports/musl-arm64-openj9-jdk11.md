---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 07:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795524384 64
1795524389 64
1795524394 64
1795524399 64
1795524404 64
1795524409 64
1795524414 64
1795524419 64
1795524424 64
1795524429 64
1795524434 64
1795524439 64
1795524444 64
1795524449 64
1795524454 64
1795524459 64
1795524464 64
1795524469 64
1795524474 64
1795524479 64
```
</details>

---

