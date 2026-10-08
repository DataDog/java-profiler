---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 09:45:18 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 12 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1791466806 48
1791466811 48
1791466816 48
1791466821 48
1791466826 48
1791466831 48
1791466836 48
1791466841 48
1791466846 48
1791466851 39
1791466856 39
1791466861 39
1791466866 39
1791466871 39
1791466876 39
1791466881 37
1791466886 37
1791466891 37
1791466896 37
1791466901 37
```
</details>

---

