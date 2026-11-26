---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 16:09:03 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795727045 64
1795727050 64
1795727055 64
1795727060 64
1795727065 64
1795727070 64
1795727075 64
1795727080 64
1795727085 64
1795727090 64
1795727095 64
1795727100 64
1795727105 64
1795727110 64
1795727115 64
1795727120 64
1795727125 64
1795727130 64
1795727135 64
1795727140 64
```
</details>

---

