---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 12:24:20 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 7 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792772382 43
1792772387 43
1792772392 43
1792772397 43
1792772402 43
1792772407 43
1792772412 43
1792772417 48
1792772422 48
1792772427 48
1792772432 48
1792772437 48
1792772442 48
1792772447 48
1792772452 48
1792772457 48
1792772462 48
1792772467 44
1792772472 44
1792772477 44
```
</details>

---

