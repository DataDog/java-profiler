---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:33:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1795015628 41
1795015633 41
1795015638 41
1795015643 46
1795015648 46
1795015653 46
1795015658 46
1795015663 46
1795015668 46
1795015673 46
1795015678 46
1795015683 46
1795015688 46
1795015693 46
1795015698 46
1795015703 46
1795015708 46
1795015713 46
1795015718 46
1795015723 46
```
</details>

---

