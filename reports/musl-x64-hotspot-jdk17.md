---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 58-64 cores)</summary>

```
1795793613 58
1795793618 58
1795793623 58
1795793628 60
1795793633 60
1795793638 60
1795793643 60
1795793648 60
1795793653 60
1795793658 60
1795793663 60
1795793668 64
1795793673 64
1795793678 64
1795793683 64
1795793688 64
1795793693 64
1795793698 64
1795793703 64
1795793708 64
```
</details>

---

