---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 14:48:06 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 59-77 cores)</summary>

```
1794253426 59
1794253431 59
1794253436 59
1794253441 62
1794253446 62
1794253451 62
1794253456 60
1794253461 60
1794253466 60
1794253471 60
1794253476 60
1794253481 60
1794253486 60
1794253491 60
1794253496 62
1794253501 62
1794253506 62
1794253511 62
1794253516 62
1794253521 62
```
</details>

---

