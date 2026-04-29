---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 14:43:11 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 20-60 cores)</summary>

```
1777487730 20
1777487735 60
1777487740 60
1777487745 24
1777487750 24
1777487755 24
1777487760 24
1777487765 24
1777487771 24
1777487776 24
1777487781 24
1777487786 24
1777487791 24
1777487796 24
1777487801 24
1777487806 24
1777487811 24
1777487816 24
1777487821 24
1777487826 24
```
</details>

---

