---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:26:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794489751 48
1794489756 48
1794489761 48
1794489766 48
1794489771 48
1794489776 48
1794489781 48
1794489786 48
1794489791 48
1794489796 48
1794489801 48
1794489806 48
1794489811 48
1794489816 43
1794489821 43
1794489826 43
1794489831 43
1794489836 43
1794489841 43
1794489846 43
```
</details>

---

