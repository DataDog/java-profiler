---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:06:40 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1789743573 45
1789743578 45
1789743583 45
1789743588 45
1789743593 45
1789743598 45
1789743603 45
1789743608 45
1789743613 46
1789743618 46
1789743623 46
1789743628 46
1789743633 40
1789743638 40
1789743643 40
1789743648 40
1789743653 40
1789743658 40
1789743663 40
1789743668 40
```
</details>

---

