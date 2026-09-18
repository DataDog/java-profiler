---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:27:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 37-42 cores)</summary>

```
1789737659 38
1789737664 38
1789737669 38
1789737674 38
1789737679 38
1789737684 38
1789737689 38
1789737694 38
1789737699 38
1789737704 37
1789737709 37
1789737714 37
1789737719 37
1789737724 37
1789737729 37
1789737734 37
1789737739 37
1789737744 37
1789737749 37
1789737754 37
```
</details>

---

