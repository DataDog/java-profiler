---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 09:26:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1787318501 48
1787318506 48
1787318511 48
1787318516 48
1787318521 48
1787318526 48
1787318531 48
1787318536 36
1787318541 36
1787318546 36
1787318551 36
1787318556 36
1787318561 36
1787318566 36
1787318571 36
1787318576 36
1787318581 36
1787318586 36
1787318591 36
1787318596 36
```
</details>

---

