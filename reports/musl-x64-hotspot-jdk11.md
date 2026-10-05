---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 13:24:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 990 |
| Sample Rate | 16.50/sec |
| Health Score | 1031% |
| Threads | 12 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1791220769 80
1791220774 80
1791220779 80
1791220784 80
1791220789 80
1791220794 80
1791220799 80
1791220804 80
1791220809 80
1791220814 80
1791220819 80
1791220824 80
1791220829 80
1791220834 80
1791220839 80
1791220844 80
1791220849 80
1791220854 82
1791220859 82
1791220864 82
```
</details>

---

