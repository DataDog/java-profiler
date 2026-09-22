---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 00:56:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 11-48 cores)</summary>

```
1790052780 11
1790052785 11
1790052790 11
1790052795 11
1790052800 11
1790052805 11
1790052810 11
1790052815 11
1790052820 11
1790052825 11
1790052830 11
1790052835 11
1790052840 11
1790052845 11
1790052850 48
1790052855 48
1790052860 11
1790052865 11
1790052870 11
1790052875 11
```
</details>

---

