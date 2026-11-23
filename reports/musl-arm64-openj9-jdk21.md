---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:08:50 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 13 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795424528 24
1795424533 24
1795424538 24
1795424543 24
1795424548 24
1795424553 24
1795424558 24
1795424563 24
1795424568 24
1795424573 24
1795424578 24
1795424583 24
1795424588 24
1795424593 24
1795424598 29
1795424603 29
1795424608 29
1795424613 29
1795424618 29
1795424623 29
```
</details>

---

