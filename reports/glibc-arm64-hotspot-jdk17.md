---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:42:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 14 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794429451 43
1794429456 43
1794429461 43
1794429466 43
1794429471 43
1794429476 43
1794429481 43
1794429486 43
1794429491 43
1794429496 48
1794429501 48
1794429506 48
1794429511 48
1794429516 48
1794429521 48
1794429526 48
1794429531 48
1794429536 48
1794429541 48
1794429546 48
```
</details>

---

