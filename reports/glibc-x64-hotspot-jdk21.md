---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 14:43:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1777487728 32
1777487733 32
1777487738 32
1777487743 32
1777487748 32
1777487753 32
1777487758 26
1777487763 26
1777487768 26
1777487773 26
1777487778 28
1777487783 28
1777487788 28
1777487793 28
1777487798 28
1777487803 28
1777487808 28
1777487813 28
1777487818 28
1777487823 28
```
</details>

---

