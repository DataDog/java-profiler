---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 01:05:54 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793163672 43
1793163677 48
1793163682 48
1793163687 48
1793163693 48
1793163698 48
1793163703 48
1793163708 48
1793163713 48
1793163718 48
1793163723 48
1793163728 48
1793163733 48
1793163738 48
1793163743 48
1793163748 48
1793163753 48
1793163758 48
1793163763 48
1793163768 48
```
</details>

---

