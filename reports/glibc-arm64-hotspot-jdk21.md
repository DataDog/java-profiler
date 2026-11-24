---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 07:06:37 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795521779 64
1795521784 64
1795521789 64
1795521794 64
1795521799 64
1795521804 64
1795521809 64
1795521814 64
1795521819 64
1795521825 64
1795521830 64
1795521835 64
1795521840 64
1795521845 64
1795521850 64
1795521855 64
1795521860 64
1795521865 64
1795521870 64
1795521875 64
```
</details>

---

