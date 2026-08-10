---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:45:23 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1786358477 62
1786358482 62
1786358487 62
1786358492 62
1786358497 64
1786358502 64
1786358507 64
1786358512 64
1786358517 64
1786358522 64
1786358527 51
1786358532 51
1786358537 51
1786358542 46
1786358547 46
1786358552 46
1786358557 46
1786358562 46
1786358567 46
1786358572 46
```
</details>

---

