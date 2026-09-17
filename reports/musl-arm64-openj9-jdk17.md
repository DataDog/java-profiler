---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 13:54:16 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789667206 47
1789667211 47
1789667216 47
1789667221 47
1789667226 47
1789667231 47
1789667236 47
1789667241 47
1789667246 47
1789667251 48
1789667256 48
1789667261 48
1789667266 48
1789667271 48
1789667276 48
1789667281 48
1789667286 48
1789667291 48
1789667296 48
1789667301 43
```
</details>

---

