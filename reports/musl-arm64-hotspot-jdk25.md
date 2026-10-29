---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 11:50:45 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 14 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1793288572 53
1793288577 53
1793288582 53
1793288587 53
1793288592 53
1793288597 53
1793288602 53
1793288607 53
1793288612 53
1793288617 53
1793288622 53
1793288627 53
1793288632 53
1793288637 53
1793288642 53
1793288647 53
1793288652 53
1793288657 53
1793288662 53
1793288667 53
```
</details>

---

