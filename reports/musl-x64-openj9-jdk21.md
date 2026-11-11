---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:42:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (5 unique values: 65-91 cores)</summary>

```
1794429421 73
1794429426 80
1794429431 80
1794429436 80
1794429441 80
1794429446 80
1794429451 80
1794429456 80
1794429461 80
1794429466 82
1794429471 82
1794429476 82
1794429481 82
1794429486 82
1794429491 65
1794429496 65
1794429501 65
1794429506 65
1794429511 65
1794429516 65
```
</details>

---

