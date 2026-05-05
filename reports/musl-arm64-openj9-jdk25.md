---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777983466 64
1777983471 64
1777983476 64
1777983481 64
1777983486 64
1777983491 64
1777983496 64
1777983501 64
1777983506 64
1777983511 64
1777983516 64
1777983521 64
1777983526 64
1777983531 64
1777983536 64
1777983541 64
1777983546 64
1777983551 64
1777983556 64
1777983561 64
```
</details>

---

