---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-19 00:58:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789793659 32
1789793664 32
1789793669 32
1789793674 32
1789793679 32
1789793684 32
1789793689 32
1789793694 32
1789793699 32
1789793704 32
1789793709 32
1789793714 32
1789793719 32
1789793724 32
1789793729 32
1789793734 32
1789793739 32
1789793744 32
1789793749 32
1789793754 32
```
</details>

---

