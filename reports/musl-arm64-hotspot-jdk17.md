---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1778512725 57
1778512730 57
1778512735 57
1778512740 57
1778512745 57
1778512750 57
1778512755 57
1778512760 57
1778512765 57
1778512770 57
1778512775 57
1778512780 57
1778512785 57
1778512790 57
1778512795 64
1778512800 64
1778512805 64
1778512810 64
1778512815 53
1778512820 53
```
</details>

---

