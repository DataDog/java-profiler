---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:31:53 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1795012053 28
1795012058 28
1795012063 28
1795012068 28
1795012073 28
1795012078 28
1795012083 28
1795012088 28
1795012093 28
1795012098 28
1795012103 28
1795012108 28
1795012113 28
1795012118 28
1795012123 64
1795012128 64
1795012133 64
1795012138 64
1795012143 64
1795012148 64
```
</details>

---

