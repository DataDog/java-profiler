---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:57:02 EST

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
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794509519 43
1794509524 43
1794509529 43
1794509535 43
1794509540 43
1794509545 43
1794509550 43
1794509555 43
1794509560 43
1794509565 43
1794509570 43
1794509575 48
1794509580 48
1794509585 48
1794509590 48
1794509595 48
1794509600 48
1794509605 48
1794509610 48
1794509615 48
```
</details>

---

