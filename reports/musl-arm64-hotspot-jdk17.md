---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795382898 49
1795382903 49
1795382908 49
1795382913 49
1795382918 49
1795382923 44
1795382928 44
1795382933 44
1795382938 44
1795382943 44
1795382948 44
1795382953 44
1795382958 44
1795382963 44
1795382968 44
1795382973 44
1795382978 44
1795382983 49
1795382988 49
1795382993 49
```
</details>

---

