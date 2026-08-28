---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-28 14:02:38 EDT

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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787939888 64
1787939893 64
1787939898 64
1787939903 64
1787939908 64
1787939913 64
1787939918 64
1787939923 64
1787939928 64
1787939933 64
1787939938 64
1787939943 64
1787939948 64
1787939953 64
1787939958 64
1787939963 64
1787939968 64
1787939973 64
1787939978 64
1787939983 64
```
</details>

---

