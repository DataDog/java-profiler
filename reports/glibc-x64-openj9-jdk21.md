---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:45:06 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 27-48 cores)</summary>

```
1778582460 32
1778582465 32
1778582470 32
1778582475 27
1778582480 27
1778582485 27
1778582490 27
1778582495 27
1778582500 32
1778582505 32
1778582510 30
1778582515 30
1778582520 30
1778582525 30
1778582530 30
1778582535 30
1778582540 30
1778582545 30
1778582550 30
1778582555 30
```
</details>

---

