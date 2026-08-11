---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 15:09:08 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 17-35 cores)</summary>

```
1786475003 35
1786475008 35
1786475013 35
1786475018 35
1786475023 35
1786475028 35
1786475033 35
1786475038 35
1786475043 35
1786475048 35
1786475053 35
1786475058 22
1786475063 22
1786475068 22
1786475073 22
1786475078 17
1786475083 17
1786475088 17
1786475093 17
1786475098 17
```
</details>

---

