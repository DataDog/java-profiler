---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:59:22 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 76-84 cores)</summary>

```
1795452904 76
1795452909 76
1795452914 76
1795452919 76
1795452924 76
1795452929 76
1795452934 76
1795452939 76
1795452944 76
1795452949 76
1795452954 84
1795452959 84
1795452964 84
1795452970 84
1795452975 84
1795452980 84
1795452985 84
1795452990 84
1795452995 84
1795453000 84
```
</details>

---

