---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:11:56 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 30-47 cores)</summary>

```
1789743498 30
1789743503 30
1789743508 30
1789743513 30
1789743518 30
1789743523 30
1789743528 30
1789743533 30
1789743538 30
1789743543 30
1789743548 30
1789743553 47
1789743558 47
1789743563 47
1789743568 47
1789743573 47
1789743578 47
1789743583 47
1789743588 47
1789743593 47
```
</details>

---

