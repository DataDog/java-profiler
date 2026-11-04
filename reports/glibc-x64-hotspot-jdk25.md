---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 12:28:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1793812800 32
1793812805 32
1793812810 32
1793812815 32
1793812820 30
1793812825 30
1793812830 30
1793812835 30
1793812840 30
1793812845 30
1793812850 30
1793812855 30
1793812860 22
1793812865 22
1793812870 22
1793812875 22
1793812880 22
1793812885 22
1793812890 22
1793812895 22
```
</details>

---

