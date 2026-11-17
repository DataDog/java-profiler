---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:58:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794930697 46
1794930702 46
1794930707 51
1794930712 51
1794930717 51
1794930722 51
1794930727 51
1794930732 51
1794930737 51
1794930742 51
1794930747 51
1794930752 51
1794930757 51
1794930762 51
1794930767 51
1794930772 51
1794930777 51
1794930782 51
1794930787 51
1794930792 51
```
</details>

---

