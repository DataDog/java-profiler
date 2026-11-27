---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795793623 64
1795793628 64
1795793633 64
1795793638 64
1795793643 64
1795793648 64
1795793653 64
1795793658 64
1795793663 64
1795793668 64
1795793673 64
1795793678 64
1795793683 64
1795793688 64
1795793693 64
1795793698 64
1795793703 64
1795793708 64
1795793713 64
1795793718 64
```
</details>

---

