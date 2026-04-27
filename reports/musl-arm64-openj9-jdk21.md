---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777325198 64
1777325203 64
1777325208 64
1777325213 64
1777325218 64
1777325223 64
1777325228 64
1777325233 64
1777325238 64
1777325243 64
1777325248 64
1777325253 64
1777325258 64
1777325263 64
1777325268 64
1777325273 64
1777325278 64
1777325284 64
1777325289 64
1777325294 64
```
</details>

---

