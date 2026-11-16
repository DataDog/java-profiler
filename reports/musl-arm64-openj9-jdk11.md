---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:32:00 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794850017 40
1794850022 40
1794850027 40
1794850032 40
1794850037 40
1794850042 40
1794850047 40
1794850052 40
1794850057 40
1794850062 40
1794850067 40
1794850072 40
1794850077 40
1794850082 40
1794850087 40
1794850092 40
1794850097 40
1794850102 40
1794850107 40
1794850112 40
```
</details>

---

