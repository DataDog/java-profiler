---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:49:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795707917 64
1795707922 64
1795707927 64
1795707932 64
1795707937 64
1795707942 64
1795707947 64
1795707952 64
1795707957 64
1795707962 64
1795707967 64
1795707972 64
1795707977 64
1795707983 64
1795707988 64
1795707993 64
1795707998 64
1795708003 64
1795708008 64
1795708013 64
```
</details>

---

