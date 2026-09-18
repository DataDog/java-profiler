---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:11:57 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1789743498 42
1789743503 42
1789743508 42
1789743513 42
1789743518 42
1789743523 42
1789743528 42
1789743533 45
1789743538 45
1789743543 45
1789743548 45
1789743553 45
1789743558 45
1789743563 45
1789743568 45
1789743573 45
1789743578 45
1789743583 45
1789743588 47
1789743593 47
```
</details>

---

