---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:46:39 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 63-89 cores)</summary>

```
1792672898 65
1792672903 65
1792672908 65
1792672913 65
1792672918 65
1792672923 65
1792672928 65
1792672933 65
1792672938 89
1792672943 89
1792672948 63
1792672953 63
1792672958 63
1792672963 65
1792672968 65
1792672973 65
1792672978 65
1792672983 65
1792672988 65
1792672993 65
```
</details>

---

