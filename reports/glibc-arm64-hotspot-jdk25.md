---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 06:42:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 11 |
| Allocations | 108 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 30-45 cores)</summary>

```
1795174698 31
1795174703 31
1795174708 31
1795174713 31
1795174718 31
1795174723 31
1795174728 31
1795174733 31
1795174738 31
1795174743 30
1795174748 30
1795174753 30
1795174758 30
1795174763 30
1795174768 30
1795174773 30
1795174778 30
1795174783 30
1795174788 30
1795174793 45
```
</details>

---

