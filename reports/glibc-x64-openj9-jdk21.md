---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:39:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1795451643 55
1795451648 55
1795451653 55
1795451658 55
1795451663 55
1795451668 55
1795451673 55
1795451678 55
1795451683 57
1795451688 57
1795451693 57
1795451698 57
1795451703 57
1795451708 57
1795451713 57
1795451718 57
1795451723 57
1795451728 57
1795451733 57
1795451738 57
```
</details>

---

