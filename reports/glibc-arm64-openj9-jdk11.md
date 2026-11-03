---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 21:59:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1793674465 43
1793674470 43
1793674475 43
1793674480 43
1793674485 43
1793674490 43
1793674495 38
1793674500 38
1793674505 38
1793674510 38
1793674515 38
1793674520 38
1793674525 38
1793674530 38
1793674535 38
1793674540 38
1793674545 38
1793674550 38
1793674555 39
1793674560 39
```
</details>

---

