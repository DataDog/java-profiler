---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:23:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789737500 47
1789737505 47
1789737510 47
1789737515 47
1789737520 47
1789737525 47
1789737530 47
1789737535 47
1789737540 47
1789737545 47
1789737550 47
1789737555 47
1789737560 47
1789737565 47
1789737570 47
1789737575 47
1789737580 47
1789737585 47
1789737590 47
1789737595 47
```
</details>

---

