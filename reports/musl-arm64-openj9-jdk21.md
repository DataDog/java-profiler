---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 14:01:22 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795200974 50
1795200979 50
1795200984 50
1795200989 50
1795200994 50
1795200999 50
1795201004 50
1795201009 50
1795201014 50
1795201019 50
1795201024 50
1795201029 50
1795201034 50
1795201039 50
1795201044 50
1795201049 50
1795201054 50
1795201059 50
1795201064 50
1795201069 50
```
</details>

---

