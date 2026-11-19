---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:09:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795129583 36
1795129588 36
1795129593 36
1795129598 36
1795129603 36
1795129608 36
1795129613 36
1795129618 36
1795129623 36
1795129628 36
1795129633 36
1795129638 36
1795129643 36
1795129648 36
1795129653 36
1795129658 36
1795129663 36
1795129668 36
1795129673 36
1795129678 36
```
</details>

---

