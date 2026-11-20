---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:08:05 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795172591 50
1795172596 50
1795172602 50
1795172607 50
1795172612 50
1795172617 50
1795172622 50
1795172627 50
1795172632 50
1795172637 50
1795172642 50
1795172647 50
1795172652 50
1795172657 50
1795172662 50
1795172667 50
1795172672 50
1795172677 50
1795172682 50
1795172687 50
```
</details>

---

