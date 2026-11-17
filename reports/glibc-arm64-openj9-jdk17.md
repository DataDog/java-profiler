---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:30:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 11 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 26-46 cores)</summary>

```
1794943528 33
1794943533 33
1794943538 33
1794943543 33
1794943548 33
1794943553 33
1794943558 33
1794943563 46
1794943568 46
1794943573 26
1794943578 26
1794943583 26
1794943588 26
1794943593 26
1794943598 26
1794943603 26
1794943608 26
1794943613 31
1794943618 31
1794943623 31
```
</details>

---

