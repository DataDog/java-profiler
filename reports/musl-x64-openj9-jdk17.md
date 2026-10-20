---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:11:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1792504983 27
1792504988 27
1792504993 27
1792504998 27
1792505003 25
1792505008 25
1792505013 25
1792505018 25
1792505023 30
1792505028 30
1792505033 30
1792505038 30
1792505043 32
1792505048 32
1792505053 32
1792505058 32
1792505063 32
1792505068 32
1792505073 32
1792505078 32
```
</details>

---

