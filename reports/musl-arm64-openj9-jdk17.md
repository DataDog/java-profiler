---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:42:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1778582221 49
1778582226 49
1778582231 49
1778582237 49
1778582242 49
1778582247 49
1778582252 49
1778582257 49
1778582262 49
1778582267 49
1778582272 49
1778582277 49
1778582282 49
1778582287 49
1778582292 49
1778582297 49
1778582302 49
1778582307 49
1778582312 49
1778582317 49
```
</details>

---

