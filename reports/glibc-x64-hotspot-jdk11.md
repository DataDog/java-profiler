---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-13 05:44:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (6 unique values: 62-84 cores)</summary>

```
1773394752 62
1773394757 62
1773394762 72
1773394767 72
1773394772 72
1773394777 76
1773394782 76
1773394787 80
1773394792 80
1773394797 80
1773394802 80
1773394807 80
1773394812 80
1773394817 84
1773394822 84
1773394827 84
1773394832 84
1773394837 84
1773394842 84
1773394847 80
```
</details>

---

