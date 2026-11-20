---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 13:22:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795198614 45
1795198619 45
1795198624 45
1795198629 45
1795198634 45
1795198639 50
1795198644 50
1795198649 50
1795198654 50
1795198659 50
1795198664 50
1795198669 50
1795198674 50
1795198679 50
1795198684 50
1795198689 64
1795198694 64
1795198699 64
1795198704 64
1795198709 64
```
</details>

---

