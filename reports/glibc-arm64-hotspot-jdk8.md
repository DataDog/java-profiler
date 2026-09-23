---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-23 11:28:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 17-59 cores)</summary>

```
1790176996 22
1790177001 22
1790177007 22
1790177012 22
1790177017 22
1790177022 22
1790177027 22
1790177032 17
1790177037 17
1790177042 59
1790177047 59
1790177052 59
1790177057 59
1790177062 45
1790177067 45
1790177072 45
1790177077 45
1790177082 45
1790177087 40
1790177092 40
```
</details>

---

