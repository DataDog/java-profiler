---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 14:43:10 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 72-83 cores)</summary>

```
1777487776 83
1777487781 83
1777487786 83
1777487791 83
1777487796 79
1777487801 79
1777487806 79
1777487811 79
1777487816 79
1777487821 74
1777487826 74
1777487831 72
1777487836 72
1777487841 72
1777487846 72
1777487851 72
1777487856 72
1777487861 72
1777487866 72
1777487871 72
```
</details>

---

