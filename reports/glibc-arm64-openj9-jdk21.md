---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 00:07:57 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 11 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793768547 32
1793768552 32
1793768557 32
1793768562 32
1793768567 32
1793768572 32
1793768577 32
1793768582 32
1793768587 32
1793768592 32
1793768597 32
1793768602 32
1793768607 32
1793768612 32
1793768617 32
1793768622 32
1793768627 32
1793768632 32
1793768637 32
1793768642 32
```
</details>

---

