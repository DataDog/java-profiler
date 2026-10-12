---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-11 23:09:31 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 12-17 cores)</summary>

```
1791774057 12
1791774062 12
1791774067 12
1791774072 12
1791774077 12
1791774082 12
1791774087 12
1791774092 12
1791774097 12
1791774102 12
1791774107 12
1791774112 17
1791774117 17
1791774122 17
1791774127 17
1791774132 17
1791774137 17
1791774142 17
1791774147 17
1791774152 15
```
</details>

---

