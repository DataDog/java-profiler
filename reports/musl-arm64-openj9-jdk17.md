---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 08:05:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 14 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (3 unique values: 33-48 cores)</summary>

```
1794402072 33
1794402077 33
1794402082 33
1794402087 33
1794402092 33
1794402097 33
1794402102 43
1794402108 43
1794402113 43
1794402118 43
1794402123 43
1794402128 43
1794402133 43
1794402138 43
1794402143 43
1794402148 43
1794402153 43
1794402158 43
1794402163 43
1794402168 43
```
</details>

---

