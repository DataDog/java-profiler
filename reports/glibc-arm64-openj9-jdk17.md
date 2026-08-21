---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 15:09:50 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1787339141 41
1787339146 41
1787339151 41
1787339156 41
1787339161 41
1787339166 41
1787339171 41
1787339176 41
1787339181 41
1787339186 46
1787339191 46
1787339196 46
1787339201 46
1787339207 46
1787339212 46
1787339217 46
1787339222 46
1787339227 46
1787339232 46
1787339237 48
```
</details>

---

