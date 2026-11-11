---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:42:11 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (5 unique values: 84-92 cores)</summary>

```
1794429406 87
1794429411 87
1794429416 87
1794429421 87
1794429426 87
1794429431 87
1794429436 87
1794429441 90
1794429446 90
1794429451 90
1794429456 90
1794429461 90
1794429466 90
1794429471 90
1794429476 90
1794429481 90
1794429486 88
1794429491 88
1794429496 88
1794429501 88
```
</details>

---

