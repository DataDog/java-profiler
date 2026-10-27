---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 15:45:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793130043 64
1793130048 64
1793130053 64
1793130058 64
1793130063 64
1793130068 64
1793130073 64
1793130078 64
1793130083 64
1793130088 64
1793130093 64
1793130098 64
1793130103 64
1793130108 64
1793130113 64
1793130118 64
1793130123 64
1793130128 64
1793130133 64
1793130138 64
```
</details>

---

