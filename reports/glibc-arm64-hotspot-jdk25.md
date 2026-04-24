---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 11:36:23 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777044698 64
1777044703 64
1777044708 64
1777044713 64
1777044718 64
1777044723 64
1777044728 64
1777044733 64
1777044738 64
1777044743 64
1777044748 64
1777044753 64
1777044758 64
1777044763 64
1777044768 64
1777044773 64
1777044778 64
1777044783 64
1777044788 64
1777044793 64
```
</details>

---

