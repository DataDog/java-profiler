---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 15:37:58 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795465937 44
1795465942 44
1795465947 44
1795465952 44
1795465957 44
1795465962 44
1795465967 44
1795465972 44
1795465977 44
1795465982 44
1795465987 44
1795465992 44
1795465997 44
1795466002 44
1795466007 44
1795466012 44
1795466017 44
1795466022 44
1795466027 44
1795466032 44
```
</details>

---

