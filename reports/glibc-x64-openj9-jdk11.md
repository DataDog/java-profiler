---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-03 14:43:05 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1788460726 30
1788460731 30
1788460736 30
1788460741 30
1788460746 30
1788460751 30
1788460756 30
1788460761 28
1788460766 28
1788460771 28
1788460776 28
1788460781 28
1788460786 28
1788460791 30
1788460796 30
1788460801 30
1788460806 30
1788460811 30
1788460816 30
1788460821 28
```
</details>

---

