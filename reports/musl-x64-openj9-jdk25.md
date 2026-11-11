---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 10:44:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1794411576 84
1794411581 84
1794411586 84
1794411591 84
1794411596 84
1794411601 84
1794411606 84
1794411611 88
1794411616 88
1794411621 88
1794411626 88
1794411631 88
1794411636 88
1794411641 88
1794411646 88
1794411651 88
1794411656 88
1794411661 88
1794411666 88
1794411671 88
```
</details>

---

