---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 18:31:12 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
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
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1786400770 14
1786400775 14
1786400780 14
1786400785 14
1786400790 14
1786400795 14
1786400800 34
1786400805 34
1786400810 34
1786400815 34
1786400820 34
1786400825 34
1786400830 34
1786400835 34
1786400840 34
1786400845 34
1786400850 34
1786400855 34
1786400860 34
1786400865 34
```
</details>

---

