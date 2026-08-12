---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 05:20:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786526163 30
1786526168 30
1786526173 30
1786526178 30
1786526183 30
1786526188 30
1786526193 30
1786526198 30
1786526203 30
1786526208 32
1786526213 32
1786526218 32
1786526223 32
1786526228 32
1786526233 32
1786526238 32
1786526243 32
1786526248 32
1786526253 32
1786526258 32
```
</details>

---

