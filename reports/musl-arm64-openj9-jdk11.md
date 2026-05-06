---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:48:58 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778093017 64
1778093022 64
1778093027 64
1778093032 64
1778093037 64
1778093042 64
1778093047 64
1778093052 64
1778093058 64
1778093063 64
1778093068 64
1778093073 64
1778093078 64
1778093083 64
1778093088 64
1778093093 64
1778093098 64
1778093103 64
1778093108 64
1778093113 64
```
</details>

---

