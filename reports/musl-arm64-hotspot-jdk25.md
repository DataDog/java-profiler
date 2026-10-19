---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 09:18:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 34-37 cores)</summary>

```
1792415640 37
1792415645 37
1792415650 37
1792415655 37
1792415660 37
1792415665 37
1792415670 37
1792415675 37
1792415680 37
1792415685 34
1792415690 34
1792415695 34
1792415700 34
1792415705 34
1792415710 34
1792415715 34
1792415720 34
1792415725 34
1792415730 34
1792415735 35
```
</details>

---

