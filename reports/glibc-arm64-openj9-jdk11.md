---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:31 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 305 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 12 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1790336012 39
1790336017 39
1790336022 39
1790336027 39
1790336032 39
1790336037 39
1790336042 39
1790336047 48
1790336052 48
1790336057 48
1790336063 48
1790336068 46
1790336073 46
1790336078 46
1790336083 46
1790336088 46
1790336093 46
1790336098 46
1790336103 46
1790336108 46
```
</details>

---

