---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794393741 46
1794393746 46
1794393751 46
1794393756 46
1794393761 46
1794393766 46
1794393771 46
1794393776 46
1794393781 51
1794393786 51
1794393791 51
1794393796 51
1794393801 51
1794393806 51
1794393811 51
1794393816 51
1794393821 51
1794393826 51
1794393831 51
1794393836 51
```
</details>

---

