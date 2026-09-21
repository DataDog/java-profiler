---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 03:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1789975441 19
1789975446 32
1789975451 32
1789975456 32
1789975461 32
1789975466 32
1789975471 32
1789975476 32
1789975481 32
1789975486 32
1789975491 32
1789975496 32
1789975501 32
1789975506 32
1789975511 32
1789975516 32
1789975521 32
1789975526 32
1789975531 32
1789975536 32
```
</details>

---

