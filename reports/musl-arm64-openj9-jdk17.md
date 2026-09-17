---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 15:41:05 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1789673466 39
1789673471 39
1789673476 39
1789673481 39
1789673486 39
1789673491 39
1789673496 39
1789673501 39
1789673506 39
1789673511 39
1789673516 39
1789673521 39
1789673526 39
1789673531 44
1789673536 44
1789673541 44
1789673546 44
1789673551 44
1789673556 44
1789673561 44
```
</details>

---

