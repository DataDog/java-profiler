---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 10:44:47 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1794411556 44
1794411561 44
1794411566 44
1794411571 44
1794411576 44
1794411581 44
1794411586 44
1794411591 44
1794411596 44
1794411601 44
1794411606 44
1794411611 44
1794411616 44
1794411621 44
1794411626 44
1794411631 44
1794411636 43
1794411641 43
1794411646 43
1794411651 43
```
</details>

---

