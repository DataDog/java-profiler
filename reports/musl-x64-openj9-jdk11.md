---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 10:44:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 560 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1794411591 19
1794411596 19
1794411601 19
1794411606 21
1794411611 21
1794411616 21
1794411621 21
1794411626 21
1794411631 21
1794411636 21
1794411641 21
1794411646 21
1794411651 21
1794411656 21
1794411661 21
1794411666 21
1794411671 21
1794411676 21
1794411681 21
1794411686 21
```
</details>

---

