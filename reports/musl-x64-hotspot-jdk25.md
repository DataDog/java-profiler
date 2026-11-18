---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:34:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (6 unique values: 67-90 cores)</summary>

```
1795015800 71
1795015805 71
1795015810 71
1795015815 71
1795015820 71
1795015825 71
1795015830 71
1795015835 69
1795015840 69
1795015845 69
1795015850 67
1795015855 67
1795015860 67
1795015865 67
1795015870 67
1795015875 67
1795015880 78
1795015885 78
1795015890 78
1795015895 88
```
</details>

---

