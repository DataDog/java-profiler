---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1790335981 53
1790335986 53
1790335991 53
1790335996 53
1790336001 53
1790336006 53
1790336011 62
1790336016 62
1790336021 64
1790336026 64
1790336031 64
1790336036 64
1790336041 64
1790336046 64
1790336051 64
1790336056 64
1790336061 64
1790336066 64
1790336071 64
1790336076 64
```
</details>

---

