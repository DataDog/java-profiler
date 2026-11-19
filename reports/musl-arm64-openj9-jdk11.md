---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:23:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 48-50 cores)</summary>

```
1795108625 48
1795108630 48
1795108635 48
1795108640 48
1795108645 48
1795108650 48
1795108655 50
1795108660 50
1795108665 50
1795108670 50
1795108675 50
1795108680 50
1795108685 50
1795108690 50
1795108695 50
1795108700 50
1795108705 50
1795108710 50
1795108715 50
1795108720 50
```
</details>

---

