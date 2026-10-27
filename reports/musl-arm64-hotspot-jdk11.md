---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 15:45:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1793129945 43
1793129950 43
1793129955 48
1793129960 48
1793129965 48
1793129970 48
1793129975 48
1793129980 48
1793129985 48
1793129990 48
1793129995 40
1793130000 40
1793130006 40
1793130011 40
1793130016 40
1793130021 40
1793130026 40
1793130031 40
1793130036 40
1793130041 40
```
</details>

---

