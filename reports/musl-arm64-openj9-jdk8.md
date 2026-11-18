---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1795001496 30
1795001501 30
1795001506 25
1795001511 25
1795001516 25
1795001521 29
1795001526 29
1795001531 29
1795001536 29
1795001541 29
1795001546 29
1795001551 29
1795001556 29
1795001561 29
1795001566 29
1795001571 29
1795001576 29
1795001581 29
1795001586 29
1795001591 29
```
</details>

---

