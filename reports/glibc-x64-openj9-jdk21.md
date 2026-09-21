---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 38-58 cores)</summary>

```
1789982420 47
1789982425 47
1789982430 47
1789982435 47
1789982440 47
1789982445 47
1789982450 47
1789982455 47
1789982460 47
1789982465 58
1789982470 58
1789982475 58
1789982480 58
1789982485 58
1789982490 58
1789982495 48
1789982500 48
1789982505 48
1789982510 48
1789982515 38
```
</details>

---

