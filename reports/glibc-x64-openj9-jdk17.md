---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:36:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 28-53 cores)</summary>

```
1794396693 28
1794396698 28
1794396703 28
1794396708 28
1794396713 28
1794396718 28
1794396723 28
1794396728 28
1794396733 28
1794396738 28
1794396743 28
1794396748 53
1794396753 53
1794396758 53
1794396763 53
1794396768 31
1794396773 31
1794396778 29
1794396783 29
1794396788 29
```
</details>

---

