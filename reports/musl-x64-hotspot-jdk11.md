---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:07:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 66-76 cores)</summary>

```
1789743498 66
1789743503 66
1789743508 66
1789743513 66
1789743518 66
1789743523 66
1789743528 66
1789743533 66
1789743538 66
1789743543 66
1789743548 66
1789743553 76
1789743558 76
1789743563 76
1789743568 76
1789743573 66
1789743578 66
1789743583 66
1789743588 66
1789743593 66
```
</details>

---

