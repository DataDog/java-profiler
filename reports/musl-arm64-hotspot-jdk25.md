---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 14:34:10 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 10-64 cores)</summary>

```
1793125638 10
1793125643 10
1793125648 10
1793125653 10
1793125658 10
1793125663 10
1793125668 10
1793125673 10
1793125678 10
1793125683 10
1793125688 10
1793125693 10
1793125698 10
1793125703 10
1793125708 10
1793125713 10
1793125718 10
1793125723 30
1793125728 30
1793125733 30
```
</details>

---

