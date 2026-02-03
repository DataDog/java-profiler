---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:18:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770119049 27
1770119054 27
1770119059 27
1770119064 27
1770119069 32
1770119074 32
1770119079 32
1770119084 32
1770119089 32
1770119094 32
1770119099 32
1770119104 32
1770119109 32
1770119114 32
1770119119 32
1770119124 32
1770119129 32
1770119134 32
1770119139 32
1770119144 32
```
</details>

---

