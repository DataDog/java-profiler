---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-12 10:34:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 45-49 cores)</summary>

```
1773325751 45
1773325756 45
1773325761 45
1773325766 45
1773325771 47
1773325776 47
1773325781 47
1773325786 47
1773325791 47
1773325796 47
1773325801 47
1773325806 47
1773325811 47
1773325816 49
1773325821 49
1773325826 49
1773325831 49
1773325836 49
1773325841 49
1773325846 49
```
</details>

---

