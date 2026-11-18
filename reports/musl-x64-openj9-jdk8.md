---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1795001493 59
1795001498 59
1795001503 59
1795001508 59
1795001513 59
1795001518 59
1795001523 59
1795001528 59
1795001533 59
1795001538 59
1795001543 59
1795001548 59
1795001553 59
1795001558 64
1795001563 64
1795001568 64
1795001573 64
1795001578 59
1795001583 59
1795001588 61
```
</details>

---

