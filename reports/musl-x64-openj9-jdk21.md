---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 13:40:56 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 972 |
| Sample Rate | 16.20/sec |
| Health Score | 1012% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 72-88 cores)</summary>

```
1787074521 72
1787074526 72
1787074531 72
1787074536 72
1787074541 72
1787074546 72
1787074551 72
1787074556 72
1787074561 72
1787074566 72
1787074571 72
1787074576 72
1787074581 72
1787074586 72
1787074591 72
1787074596 72
1787074601 72
1787074606 88
1787074611 88
1787074616 88
```
</details>

---

