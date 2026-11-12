---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:55:48 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 84-93 cores)</summary>

```
1794487761 93
1794487766 93
1794487771 93
1794487776 93
1794487781 93
1794487786 93
1794487791 93
1794487796 93
1794487801 93
1794487806 93
1794487811 93
1794487816 93
1794487821 93
1794487826 93
1794487831 93
1794487836 93
1794487841 93
1794487846 93
1794487851 84
1794487856 84
```
</details>

---

