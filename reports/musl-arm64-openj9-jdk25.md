---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 04:49:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792658544 48
1792658549 48
1792658554 48
1792658559 48
1792658564 48
1792658569 48
1792658574 46
1792658579 46
1792658584 46
1792658589 46
1792658594 46
1792658599 46
1792658604 46
1792658609 46
1792658614 48
1792658619 48
1792658624 48
1792658629 48
1792658634 48
1792658639 48
```
</details>

---

