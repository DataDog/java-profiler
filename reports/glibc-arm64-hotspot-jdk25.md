---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
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
1795383013 23
1795383018 23
```
</details>

---

