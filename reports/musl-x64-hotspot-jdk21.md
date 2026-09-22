---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:10:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 45-59 cores)</summary>

```
1790096698 59
1790096703 59
1790096708 59
1790096713 49
1790096718 49
1790096723 45
1790096728 45
1790096733 45
1790096738 45
1790096743 45
1790096748 45
1790096753 45
1790096758 45
1790096763 45
1790096768 45
1790096773 47
1790096778 47
1790096783 47
1790096788 49
1790096793 49
```
</details>

---

