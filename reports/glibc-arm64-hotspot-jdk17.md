---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 11:31:08 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795105643 50
1795105648 50
1795105653 50
1795105658 50
1795105663 50
1795105668 50
1795105673 50
1795105678 50
1795105683 50
1795105688 50
1795105693 50
1795105698 50
1795105703 50
1795105708 50
1795105713 50
1795105718 50
1795105723 50
1795105728 50
1795105733 50
1795105738 50
```
</details>

---

