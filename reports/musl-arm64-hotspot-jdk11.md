---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 10 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795192447 50
1795192452 50
1795192457 50
1795192462 50
1795192467 50
1795192473 50
1795192478 50
1795192483 50
1795192488 50
1795192493 50
1795192498 50
1795192503 50
1795192508 50
1795192513 50
1795192518 50
1795192523 50
1795192528 50
1795192533 50
1795192538 50
1795192543 50
```
</details>

---

