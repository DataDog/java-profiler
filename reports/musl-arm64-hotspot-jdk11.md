---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1795382913 33
1795382918 33
1795382923 33
1795382928 33
1795382933 33
1795382938 33
1795382943 33
1795382948 33
1795382953 33
1795382958 33
1795382963 33
1795382968 33
1795382973 33
1795382978 33
1795382983 28
1795382988 28
1795382993 28
1795382998 28
1795383003 28
1795383008 23
```
</details>

---

