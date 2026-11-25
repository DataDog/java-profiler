---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:37:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795613566 47
1795613571 47
1795613576 47
1795613581 47
1795613586 47
1795613591 47
1795613596 47
1795613601 47
1795613606 47
1795613611 47
1795613616 47
1795613621 47
1795613626 47
1795613631 47
1795613636 47
1795613641 47
1795613646 47
1795613651 47
1795613656 47
1795613661 47
```
</details>

---

