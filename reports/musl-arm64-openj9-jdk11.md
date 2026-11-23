---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 09:03:28 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795442325 48
1795442330 64
1795442335 64
1795442340 64
1795442345 64
1795442350 64
1795442355 64
1795442360 64
1795442365 64
1795442370 64
1795442375 64
1795442380 64
1795442385 64
1795442390 64
1795442395 64
1795442400 64
1795442405 64
1795442410 64
1795442415 64
1795442420 64
```
</details>

---

