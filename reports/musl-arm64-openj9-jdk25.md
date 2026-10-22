---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 11 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792676350 48
1792676355 48
1792676360 48
1792676365 48
1792676370 48
1792676375 48
1792676380 48
1792676385 48
1792676390 48
1792676395 48
1792676400 48
1792676405 48
1792676410 48
1792676415 48
1792676420 48
1792676425 48
1792676430 48
1792676435 43
1792676440 43
1792676445 43
```
</details>

---

