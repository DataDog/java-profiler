---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-12 10:34:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 13 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 45-49 cores)</summary>

```
1773325750 45
1773325755 45
1773325760 45
1773325765 45
1773325770 47
1773325775 47
1773325780 47
1773325785 47
1773325790 47
1773325795 47
1773325800 47
1773325805 47
1773325810 47
1773325815 49
1773325820 49
1773325825 49
1773325830 49
1773325835 49
1773325840 49
1773325845 49
```
</details>

---

