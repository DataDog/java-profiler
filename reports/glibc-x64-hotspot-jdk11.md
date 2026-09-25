---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:34:09 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 56-76 cores)</summary>

```
1790332047 76
1790332052 76
1790332057 76
1790332062 76
1790332067 66
1790332072 66
1790332077 66
1790332082 66
1790332087 66
1790332092 66
1790332097 56
1790332102 56
1790332107 56
1790332112 66
1790332117 66
1790332122 66
1790332127 66
1790332132 66
1790332137 66
1790332142 66
```
</details>

---

