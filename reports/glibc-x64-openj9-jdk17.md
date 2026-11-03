---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (7 unique values: 63-93 cores)</summary>

```
1793734721 63
1793734726 63
1793734731 65
1793734736 65
1793734741 65
1793734746 65
1793734751 67
1793734756 67
1793734761 67
1793734766 67
1793734771 72
1793734776 72
1793734781 72
1793734786 72
1793734791 72
1793734796 72
1793734801 93
1793734806 93
1793734811 93
1793734816 91
```
</details>

---

