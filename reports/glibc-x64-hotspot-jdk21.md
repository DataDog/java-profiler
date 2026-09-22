---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790096712 22
1790096718 22
1790096723 22
1790096728 22
1790096733 32
1790096738 32
1790096743 22
1790096748 22
1790096753 22
1790096758 22
1790096763 22
1790096768 22
1790096773 22
1790096778 22
1790096783 22
1790096788 22
1790096793 22
1790096798 22
1790096803 22
1790096808 22
```
</details>

---

