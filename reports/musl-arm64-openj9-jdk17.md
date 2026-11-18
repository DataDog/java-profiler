---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-18 06:36:03 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1795001486 51
1795001491 51
1795001496 51
1795001501 51
1795001506 51
1795001511 51
1795001516 51
1795001521 51
1795001526 51
1795001531 51
1795001536 51
1795001541 51
1795001546 51
1795001551 51
1795001556 51
1795001561 51
1795001566 51
1795001571 51
1795001576 51
1795001581 51
```
</details>

---

