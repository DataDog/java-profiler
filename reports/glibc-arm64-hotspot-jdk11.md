---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 09:45:18 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 40-44 cores)</summary>

```
1791466765 40
1791466770 40
1791466775 40
1791466780 40
1791466785 40
1791466790 40
1791466795 40
1791466800 40
1791466805 40
1791466810 40
1791466815 40
1791466820 40
1791466825 40
1791466830 40
1791466835 40
1791466840 40
1791466845 40
1791466850 40
1791466855 40
1791466860 40
```
</details>

---

