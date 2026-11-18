---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 68-79 cores)</summary>

```
1795015795 70
1795015800 70
1795015805 70
1795015810 70
1795015815 70
1795015820 72
1795015825 72
1795015830 70
1795015835 70
1795015840 79
1795015845 79
1795015850 79
1795015855 70
1795015860 70
1795015865 70
1795015870 70
1795015875 70
1795015880 70
1795015885 70
1795015890 70
```
</details>

---

