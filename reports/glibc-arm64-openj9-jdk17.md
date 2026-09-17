---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:14:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789686500 43
1789686505 43
1789686510 43
1789686515 43
1789686520 43
1789686525 48
1789686530 48
1789686535 48
1789686540 48
1789686545 43
1789686550 43
1789686555 43
1789686560 43
1789686565 43
1789686570 43
1789686575 43
1789686580 43
1789686585 43
1789686590 43
1789686595 47
```
</details>

---

