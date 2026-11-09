---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:57:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 9 |
| Allocations | 115 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 39-43 cores)</summary>

```
1794236012 43
1794236017 43
1794236022 43
1794236027 43
1794236032 43
1794236037 43
1794236042 43
1794236047 43
1794236052 43
1794236057 43
1794236062 43
1794236067 43
1794236072 39
1794236077 39
1794236082 39
1794236087 39
1794236092 39
1794236097 39
1794236102 39
1794236107 39
```
</details>

---

