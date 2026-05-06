---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 10:50:14 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 80-96 cores)</summary>

```
1778078681 80
1778078686 80
1778078691 84
1778078696 84
1778078701 84
1778078706 84
1778078711 84
1778078716 84
1778078721 84
1778078726 84
1778078731 84
1778078736 84
1778078741 84
1778078746 84
1778078751 84
1778078756 84
1778078761 84
1778078766 84
1778078771 84
1778078776 91
```
</details>

---

