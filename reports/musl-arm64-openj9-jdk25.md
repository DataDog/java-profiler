---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:33:15 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 8 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795015605 64
1795015610 64
1795015615 64
1795015620 64
1795015625 64
1795015630 51
1795015635 51
1795015640 51
1795015646 51
1795015651 51
1795015656 51
1795015661 51
1795015666 51
1795015671 51
1795015676 51
1795015681 51
1795015686 51
1795015691 51
1795015696 51
1795015701 51
```
</details>

---

