---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:44:04 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790779119 47
1790779124 47
1790779129 47
1790779134 47
1790779139 48
1790779144 48
1790779149 48
1790779154 48
1790779159 48
1790779164 48
1790779169 48
1790779174 48
1790779179 43
1790779184 43
1790779189 43
1790779194 43
1790779199 43
1790779204 43
1790779209 43
1790779214 43
```
</details>

---

