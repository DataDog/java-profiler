---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 03:42:36 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794559022 32
1794559027 32
1794559032 32
1794559037 32
1794559042 32
1794559047 32
1794559052 32
1794559057 32
1794559062 32
1794559067 32
1794559072 32
1794559077 32
1794559083 32
1794559088 32
1794559093 32
1794559098 32
1794559103 32
1794559108 32
1794559113 32
1794559118 32
```
</details>

---

