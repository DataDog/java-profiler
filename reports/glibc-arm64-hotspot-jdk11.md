---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 08:47:47 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 34-60 cores)</summary>

```
1794922873 34
1794922878 34
1794922883 47
1794922888 47
1794922893 47
1794922898 47
1794922903 47
1794922908 47
1794922913 47
1794922918 47
1794922923 47
1794922928 47
1794922933 47
1794922938 47
1794922943 47
1794922948 47
1794922953 47
1794922958 47
1794922963 47
1794922968 47
```
</details>

---

