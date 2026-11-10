---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 12:41:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 11 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794332002 48
1794332007 48
1794332012 48
1794332017 48
1794332022 48
1794332027 48
1794332032 48
1794332037 48
1794332042 36
1794332047 36
1794332052 36
1794332057 36
1794332062 36
1794332067 36
1794332072 36
1794332077 36
1794332082 36
1794332087 36
1794332092 36
1794332097 36
```
</details>

---

