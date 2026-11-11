---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:02:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 8 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794405416 43
1794405421 43
1794405426 43
1794405431 43
1794405436 43
1794405441 48
1794405446 48
1794405451 48
1794405456 48
1794405461 47
1794405466 47
1794405471 47
1794405476 47
1794405481 47
1794405486 47
1794405491 47
1794405496 47
1794405501 47
1794405506 47
1794405511 48
```
</details>

---

