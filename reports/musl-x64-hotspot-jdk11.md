---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 12:46:38 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 25-29 cores)</summary>

```
1770140451 26
1770140456 26
1770140461 26
1770140466 26
1770140471 26
1770140476 26
1770140481 26
1770140486 28
1770140491 28
1770140496 28
1770140501 28
1770140506 25
1770140511 25
1770140516 25
1770140521 25
1770140526 25
1770140531 25
1770140536 25
1770140541 25
1770140546 25
```
</details>

---

