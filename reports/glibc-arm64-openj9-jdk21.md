---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:23:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 14-20 cores)</summary>

```
1795108654 20
1795108659 20
1795108664 20
1795108669 20
1795108674 20
1795108679 20
1795108684 20
1795108689 20
1795108694 20
1795108699 20
1795108704 20
1795108709 20
1795108714 20
1795108719 20
1795108724 20
1795108729 20
1795108734 20
1795108739 20
1795108744 20
1795108749 20
```
</details>

---

