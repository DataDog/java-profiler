---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 00:56:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 32-72 cores)</summary>

```
1790052746 32
1790052751 32
1790052756 32
1790052761 32
1790052766 32
1790052771 32
1790052776 32
1790052781 32
1790052786 34
1790052791 34
1790052796 34
1790052801 34
1790052806 34
1790052811 34
1790052816 72
1790052821 72
1790052826 39
1790052831 39
1790052836 39
1790052841 39
```
</details>

---

