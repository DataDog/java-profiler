---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 15:03:07 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (6 unique values: 35-46 cores)</summary>

```
1794340522 46
1794340527 46
1794340532 46
1794340537 46
1794340542 46
1794340547 43
1794340552 43
1794340557 38
1794340562 38
1794340567 38
1794340572 38
1794340577 38
1794340582 35
1794340587 35
1794340592 35
1794340597 35
1794340602 40
1794340607 40
1794340612 40
1794340617 40
```
</details>

---

