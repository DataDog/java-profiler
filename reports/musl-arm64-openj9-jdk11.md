---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:46:29 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1786376355 32
1786376360 32
1786376365 32
1786376370 32
1786376375 32
1786376380 32
1786376385 32
1786376390 32
1786376395 32
1786376400 32
1786376405 32
1786376410 32
1786376415 32
1786376420 32
1786376425 32
1786376430 32
1786376435 32
1786376440 32
1786376445 32
1786376450 32
```
</details>

---

