---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 09:45:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1787665002 38
1787665007 38
1787665012 43
1787665017 43
1787665022 43
1787665027 48
1787665032 48
1787665037 48
1787665042 48
1787665047 43
1787665052 43
1787665057 43
1787665062 43
1787665067 38
1787665072 38
1787665077 38
1787665082 38
1787665087 38
1787665092 38
1787665097 38
```
</details>

---

