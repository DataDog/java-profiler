---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:34:32 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1794587405 88
1794587410 88
1794587415 88
1794587420 88
1794587425 86
1794587430 86
1794587435 86
1794587440 86
1794587445 86
1794587450 86
1794587455 86
1794587460 86
1794587465 86
1794587470 86
1794587475 86
1794587480 86
1794587485 86
1794587490 86
1794587495 86
1794587500 86
```
</details>

---

