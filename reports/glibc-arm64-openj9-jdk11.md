---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:59:08 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 12 |
| Allocations | 180 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1790780084 32
1790780089 32
1790780094 32
1790780099 32
1790780104 32
1790780109 32
1790780114 32
1790780119 32
1790780124 32
1790780129 32
1790780134 52
1790780139 52
1790780144 32
1790780149 32
1790780154 32
1790780159 32
1790780164 32
1790780169 32
1790780174 32
1790780179 32
```
</details>

---

