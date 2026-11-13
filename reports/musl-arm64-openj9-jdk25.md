---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794587400 48
1794587405 48
1794587410 48
1794587415 48
1794587420 48
1794587425 28
1794587430 28
1794587435 28
1794587440 28
1794587445 28
1794587450 28
1794587455 28
1794587460 28
1794587465 28
1794587470 28
1794587476 28
1794587481 28
1794587486 28
1794587491 28
1794587496 28
```
</details>

---

