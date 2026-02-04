---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-04 09:27:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 957 |
| Sample Rate | 15.95/sec |
| Health Score | 997% |
| Threads | 14 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 60-69 cores)</summary>

```
1770214948 69
1770214953 69
1770214958 69
1770214963 69
1770214968 69
1770214973 69
1770214978 69
1770214983 69
1770214988 60
1770214993 60
1770214998 60
1770215003 60
1770215008 60
1770215013 64
1770215018 64
1770215023 64
1770215028 64
1770215033 64
1770215038 64
1770215043 64
```
</details>

---

