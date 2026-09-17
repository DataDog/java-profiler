---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 14:20:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1789668964 48
1789668969 48
1789668974 48
1789668980 48
1789668985 48
1789668990 48
1789668995 48
1789669000 48
1789669005 48
1789669010 48
1789669015 48
1789669020 48
1789669025 48
1789669030 48
1789669035 48
1789669040 48
1789669045 48
1789669050 48
1789669055 48
1789669060 48
```
</details>

---

