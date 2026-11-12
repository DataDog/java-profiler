---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1794487435 43
1794487440 43
1794487445 43
1794487450 43
1794487455 43
1794487460 43
1794487465 43
1794487470 48
1794487475 48
1794487480 48
1794487485 48
1794487490 48
1794487495 48
1794487500 43
1794487505 43
1794487510 43
1794487515 43
1794487520 43
1794487525 43
1794487530 43
```
</details>

---

