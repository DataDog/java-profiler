---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:01:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 10 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1794480897 82
1794480902 82
1794480907 82
1794480912 82
1794480917 82
1794480922 82
1794480927 82
1794480932 82
1794480937 87
1794480942 87
1794480947 87
1794480952 87
1794480957 87
1794480962 87
1794480967 87
1794480972 85
1794480977 85
1794480982 85
1794480987 85
1794480992 85
```
</details>

---

