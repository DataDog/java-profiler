---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:57:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 40-48 cores)</summary>

```
1794509526 48
1794509531 48
1794509536 48
1794509541 48
1794509546 48
1794509551 48
1794509556 48
1794509561 48
1794509566 48
1794509571 48
1794509576 48
1794509581 48
1794509586 48
1794509591 48
1794509596 48
1794509601 48
1794509606 43
1794509611 43
1794509616 43
1794509621 43
```
</details>

---

