---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:35:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1789673390 76
1789673395 76
1789673400 76
1789673405 76
1789673410 76
1789673415 76
1789673420 76
1789673425 76
1789673430 76
1789673435 76
1789673440 80
1789673445 80
1789673450 80
1789673455 80
1789673460 80
1789673465 80
1789673470 80
1789673475 80
1789673480 80
1789673485 80
```
</details>

---

