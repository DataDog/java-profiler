---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 15:45:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1793129941 38
1793129946 38
1793129951 38
1793129956 38
1793129961 38
1793129966 38
1793129971 38
1793129976 38
1793129981 38
1793129986 38
1793129991 38
1793129996 38
1793130001 38
1793130006 38
1793130011 38
1793130016 40
1793130021 40
1793130026 40
1793130031 40
1793130036 40
```
</details>

---

