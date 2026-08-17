---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:05:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786971571 64
1786971576 64
1786971581 64
1786971586 64
1786971591 64
1786971596 64
1786971601 64
1786971606 64
1786971611 64
1786971616 64
1786971621 64
1786971626 64
1786971631 64
1786971636 64
1786971641 64
1786971646 64
1786971651 64
1786971656 64
1786971661 64
1786971666 64
```
</details>

---

