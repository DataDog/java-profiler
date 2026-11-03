---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:25:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793722798 40
1793722803 40
1793722808 40
1793722813 40
1793722818 40
1793722823 40
1793722828 40
1793722833 40
1793722838 40
1793722843 40
1793722848 40
1793722853 40
1793722858 40
1793722863 40
1793722868 40
1793722873 40
1793722878 40
1793722883 40
1793722888 40
1793722893 40
```
</details>

---

