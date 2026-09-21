---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789982368 48
1789982373 48
1789982378 48
1789982383 48
1789982388 48
1789982393 48
1789982398 48
1789982403 48
1789982408 48
1789982413 48
1789982418 48
1789982423 48
1789982428 48
1789982433 45
1789982438 45
1789982443 45
1789982448 45
1789982453 45
1789982458 45
1789982463 45
```
</details>

---

