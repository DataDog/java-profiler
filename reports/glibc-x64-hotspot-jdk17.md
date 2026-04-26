---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-26 15:52:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1777232924 21
1777232929 21
1777232934 21
1777232939 26
1777232944 26
1777232949 26
1777232954 26
1777232959 26
1777232964 28
1777232969 28
1777232974 28
1777232979 28
1777232984 28
1777232989 28
1777232994 28
1777232999 28
1777233004 28
1777233009 28
1777233014 32
1777233019 32
```
</details>

---

