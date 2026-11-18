---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:33:13 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1795015688 52
1795015693 52
1795015698 52
1795015703 52
1795015708 52
1795015713 52
1795015718 52
1795015723 52
1795015728 52
1795015733 52
1795015738 52
1795015743 52
1795015748 52
1795015753 52
1795015758 52
1795015763 52
1795015768 52
1795015773 52
1795015778 52
1795015783 52
```
</details>

---

