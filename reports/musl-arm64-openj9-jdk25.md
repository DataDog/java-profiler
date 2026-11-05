---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 07:42:25 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 13 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793882270 48
1793882275 48
1793882280 48
1793882285 48
1793882290 48
1793882295 48
1793882300 48
1793882305 48
1793882310 48
1793882315 48
1793882320 47
1793882325 47
1793882330 47
1793882335 47
1793882340 47
1793882345 47
1793882350 43
1793882355 43
1793882360 43
1793882365 43
```
</details>

---

