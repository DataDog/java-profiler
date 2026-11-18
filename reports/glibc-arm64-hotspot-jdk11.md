---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:34:30 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1795015835 21
1795015840 21
1795015845 21
1795015850 21
1795015855 21
1795015860 21
1795015865 21
1795015870 21
1795015875 21
1795015880 21
1795015885 21
1795015890 21
1795015895 21
1795015900 21
1795015905 21
1795015910 21
1795015915 21
1795015920 21
1795015925 21
1795015930 21
```
</details>

---

