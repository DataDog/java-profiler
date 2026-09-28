---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 09:39:40 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 7-12 cores)</summary>

```
1790602558 12
1790602563 12
1790602568 12
1790602573 12
1790602578 12
1790602583 12
1790602588 12
1790602593 12
1790602598 12
1790602603 12
1790602608 12
1790602613 12
1790602618 12
1790602623 12
1790602628 12
1790602633 12
1790602638 12
1790602643 12
1790602648 7
1790602653 7
```
</details>

---

