---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 21:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793674471 34
1793674476 34
1793674481 34
1793674486 34
1793674491 34
1793674496 34
1793674501 34
1793674506 34
1793674511 34
1793674516 34
1793674521 34
1793674526 39
1793674531 39
1793674536 34
1793674541 34
1793674546 34
1793674551 34
1793674556 34
1793674561 34
1793674566 34
```
</details>

---

