---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1789667206 92
1789667211 92
1789667216 92
1789667221 92
1789667226 92
1789667231 92
1789667236 92
1789667241 92
1789667246 92
1789667251 92
1789667256 92
1789667261 92
1789667266 94
1789667271 94
1789667276 94
1789667281 94
1789667286 94
1789667291 90
1789667296 90
1789667301 90
```
</details>

---

