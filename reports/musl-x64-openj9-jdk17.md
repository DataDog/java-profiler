---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 18:03:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (5 unique values: 26-87 cores)</summary>

```
1794524338 50
1794524343 50
1794524348 50
1794524353 50
1794524358 50
1794524363 50
1794524368 50
1794524373 50
1794524378 50
1794524384 52
1794524389 52
1794524394 52
1794524399 87
1794524404 87
1794524409 87
1794524414 87
1794524419 48
1794524424 48
1794524429 26
1794524434 26
```
</details>

---

