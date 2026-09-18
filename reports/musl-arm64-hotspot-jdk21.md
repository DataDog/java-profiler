---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:07:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1789743558 64
1789743563 64
1789743568 64
1789743573 64
1789743578 64
1789743583 64
1789743588 64
1789743593 64
1789743598 47
1789743603 47
1789743608 47
1789743613 47
1789743618 47
1789743623 47
1789743628 47
1789743633 47
1789743638 47
1789743643 47
1789743648 47
1789743653 47
```
</details>

---

