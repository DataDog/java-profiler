---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:54:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1789667206 72
1789667211 72
1789667216 72
1789667221 72
1789667226 72
1789667231 72
1789667236 72
1789667241 72
1789667246 72
1789667251 70
1789667256 70
1789667261 70
1789667266 70
1789667271 70
1789667276 70
1789667281 70
1789667286 70
1789667291 70
1789667296 70
1789667301 72
```
</details>

---

