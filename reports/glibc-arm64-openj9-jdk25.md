---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:10:44 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778090748 64
1778090753 64
1778090758 64
1778090763 64
1778090768 64
1778090773 64
1778090778 64
1778090783 64
1778090788 64
1778090793 64
1778090798 64
1778090803 64
1778090808 64
1778090814 64
1778090819 64
1778090824 64
1778090829 64
1778090834 64
1778090839 64
1778090844 64
```
</details>

---

