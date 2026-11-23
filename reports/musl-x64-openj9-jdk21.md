---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:42:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 25-45 cores)</summary>

```
1795426709 32
1795426714 32
1795426719 32
1795426724 32
1795426729 32
1795426734 36
1795426739 36
1795426744 45
1795426749 45
1795426754 45
1795426759 45
1795426764 25
1795426769 25
1795426774 25
1795426779 25
1795426784 25
1795426789 25
1795426794 25
1795426799 25
1795426804 25
```
</details>

---

