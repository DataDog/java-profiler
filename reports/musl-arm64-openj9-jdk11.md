---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 15:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1790621769 48
1790621774 48
1790621779 44
1790621784 44
1790621789 44
1790621794 44
1790621799 44
1790621804 44
1790621809 44
1790621814 44
1790621819 44
1790621824 44
1790621829 44
1790621834 44
1790621839 44
1790621844 44
1790621849 44
1790621854 44
1790621859 44
1790621864 44
```
</details>

---

