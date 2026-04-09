---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-09 12:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775750726 64
1775750731 64
1775750736 64
1775750741 64
1775750746 64
1775750751 64
1775750756 64
1775750761 64
1775750766 64
1775750771 64
1775750776 64
1775750781 64
1775750786 64
1775750791 64
1775750796 64
1775750801 64
1775750806 64
1775750811 64
1775750816 64
1775750821 64
```
</details>

---

