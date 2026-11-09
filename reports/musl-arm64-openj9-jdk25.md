---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 06:39:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1794224057 48
1794224062 48
1794224067 48
1794224072 45
1794224077 45
1794224082 45
1794224087 45
1794224092 46
1794224097 46
1794224102 46
1794224107 46
1794224112 46
1794224117 46
1794224122 46
1794224127 46
1794224132 46
1794224137 46
1794224142 46
1794224147 46
1794224152 46
```
</details>

---

