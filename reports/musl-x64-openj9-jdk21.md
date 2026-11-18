---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 67-70 cores)</summary>

```
1795001473 67
1795001478 70
1795001483 70
1795001488 70
1795001493 70
1795001498 70
1795001503 70
1795001508 67
1795001513 67
1795001518 67
1795001523 67
1795001528 67
1795001533 67
1795001538 67
1795001543 67
1795001548 67
1795001553 67
1795001558 67
1795001563 67
1795001568 69
```
</details>

---

