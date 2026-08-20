---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 06:47:25 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 13 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1787222531 44
1787222536 44
1787222541 44
1787222546 44
1787222551 44
1787222556 44
1787222561 44
1787222566 44
1787222571 44
1787222576 40
1787222581 40
1787222586 40
1787222591 40
1787222596 40
1787222601 40
1787222606 40
1787222611 40
1787222616 40
1787222621 40
1787222626 45
```
</details>

---

