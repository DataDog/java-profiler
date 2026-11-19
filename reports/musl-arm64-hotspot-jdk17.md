---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:09:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795129553 29
1795129558 29
1795129563 29
1795129568 29
1795129573 29
1795129578 29
1795129583 34
1795129588 34
1795129593 34
1795129598 34
1795129603 34
1795129608 34
1795129613 34
1795129618 34
1795129623 34
1795129628 34
1795129633 34
1795129638 34
1795129643 34
1795129648 34
```
</details>

---

