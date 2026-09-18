---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:10:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1789743483 37
1789743488 37
1789743493 37
1789743498 37
1789743503 37
1789743508 37
1789743513 37
1789743518 37
1789743523 37
1789743528 37
1789743533 37
1789743538 37
1789743543 37
1789743548 37
1789743553 37
1789743558 37
1789743563 37
1789743568 42
1789743573 42
1789743578 42
```
</details>

---

