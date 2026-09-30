---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 06:19:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1790763240 67
1790763245 67
1790763250 67
1790763255 67
1790763260 67
1790763265 67
1790763270 67
1790763275 67
1790763280 67
1790763285 67
1790763290 67
1790763295 67
1790763300 67
1790763305 65
1790763310 65
1790763315 65
1790763320 65
1790763325 67
1790763330 67
1790763335 67
```
</details>

---

