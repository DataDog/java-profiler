---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 13:41:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 12 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795545452 48
1795545457 48
1795545462 48
1795545467 48
1795545472 48
1795545477 48
1795545482 48
1795545487 48
1795545492 48
1795545497 48
1795545502 48
1795545507 48
1795545512 48
1795545517 48
1795545522 48
1795545527 48
1795545532 48
1795545537 48
1795545542 48
1795545547 64
```
</details>

---

