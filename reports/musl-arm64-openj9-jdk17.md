---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:32:25 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1786368431 51
1786368436 51
1786368441 51
1786368446 51
1786368451 51
1786368456 51
1786368461 51
1786368466 51
1786368471 51
1786368476 51
1786368481 51
1786368486 51
1786368491 51
1786368496 51
1786368501 51
1786368506 51
1786368511 64
1786368516 64
1786368521 64
1786368526 64
```
</details>

---

