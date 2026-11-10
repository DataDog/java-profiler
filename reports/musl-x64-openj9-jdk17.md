---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 14:09:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1794337445 27
1794337450 27
1794337455 27
1794337460 27
1794337465 29
1794337470 29
1794337475 29
1794337480 19
1794337485 19
1794337490 19
1794337495 19
1794337500 19
1794337505 19
1794337510 19
1794337515 19
1794337520 29
1794337525 29
1794337530 27
1794337535 27
1794337540 27
```
</details>

---

