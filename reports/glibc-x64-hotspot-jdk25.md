---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:41:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 48-70 cores)</summary>

```
1789716699 48
1789716705 48
1789716710 48
1789716715 48
1789716720 48
1789716725 48
1789716730 49
1789716735 49
1789716740 49
1789716745 49
1789716750 49
1789716755 49
1789716760 49
1789716765 49
1789716770 49
1789716775 49
1789716780 70
1789716785 70
1789716790 48
1789716795 48
```
</details>

---

