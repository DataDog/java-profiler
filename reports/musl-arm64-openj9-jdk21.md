---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1795001496 36
1795001501 36
1795001506 36
1795001511 36
1795001516 36
1795001521 36
1795001526 36
1795001531 36
1795001536 36
1795001541 36
1795001546 36
1795001551 36
1795001556 36
1795001561 36
1795001566 36
1795001571 34
1795001576 34
1795001581 34
1795001586 34
1795001591 34
```
</details>

---

