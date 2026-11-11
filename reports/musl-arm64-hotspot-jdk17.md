---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:42:10 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 10 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794429416 46
1794429421 46
1794429426 46
1794429431 46
1794429436 46
1794429441 46
1794429446 46
1794429451 46
1794429456 51
1794429461 51
1794429466 51
1794429471 51
1794429476 51
1794429481 51
1794429486 51
1794429491 51
1794429496 51
1794429501 51
1794429506 51
1794429511 51
```
</details>

---

