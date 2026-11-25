---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:36:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795620736 64
1795620741 64
1795620746 64
1795620751 64
1795620756 64
1795620761 64
1795620766 64
1795620771 64
1795620776 64
1795620781 64
1795620786 64
1795620791 64
1795620796 64
1795620801 64
1795620806 64
1795620811 64
1795620816 64
1795620821 64
1795620826 64
1795620831 64
```
</details>

---

