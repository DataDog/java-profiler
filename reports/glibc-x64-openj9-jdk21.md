---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:12:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 59-65 cores)</summary>

```
1794931760 63
1794931765 63
1794931771 63
1794931776 63
1794931781 63
1794931786 65
1794931791 65
1794931796 65
1794931801 65
1794931806 65
1794931811 65
1794931816 65
1794931821 65
1794931826 65
1794931831 65
1794931836 65
1794931841 65
1794931846 65
1794931851 65
1794931856 65
```
</details>

---

