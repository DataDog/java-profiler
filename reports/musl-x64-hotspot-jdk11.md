---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 18:13:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 8 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787609349 96
1787609354 96
1787609359 96
1787609364 96
1787609369 96
1787609374 96
1787609379 96
1787609384 96
1787609389 96
1787609394 96
1787609399 96
1787609404 96
1787609409 94
1787609414 94
1787609419 94
1787609424 94
1787609429 94
1787609434 94
1787609439 96
1787609444 96
```
</details>

---

