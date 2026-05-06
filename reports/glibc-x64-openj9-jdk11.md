---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:48:58 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 8 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 16-20 cores)</summary>

```
1778093022 20
1778093027 20
1778093032 20
1778093037 20
1778093042 20
1778093047 20
1778093052 16
1778093057 16
1778093062 16
1778093067 16
1778093072 16
1778093077 16
1778093082 16
1778093087 16
1778093092 16
1778093097 16
1778093102 16
1778093107 16
1778093112 16
1778093117 16
```
</details>

---

