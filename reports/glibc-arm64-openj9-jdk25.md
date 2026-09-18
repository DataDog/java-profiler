---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:03:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743478 48
1789743483 48
1789743488 48
1789743493 48
1789743498 48
1789743503 48
1789743508 48
1789743513 48
1789743518 48
1789743523 48
1789743528 48
1789743533 48
1789743538 48
1789743543 48
1789743548 48
1789743553 48
1789743558 48
1789743563 48
1789743568 48
1789743573 48
```
</details>

---

