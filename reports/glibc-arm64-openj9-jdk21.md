---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:34:29 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794587446 47
1794587451 47
1794587456 47
1794587461 48
1794587466 48
1794587471 48
1794587476 48
1794587481 48
1794587486 48
1794587491 48
1794587496 48
1794587501 48
1794587506 48
1794587511 48
1794587516 48
1794587521 48
1794587526 48
1794587531 48
1794587536 48
1794587541 48
```
</details>

---

