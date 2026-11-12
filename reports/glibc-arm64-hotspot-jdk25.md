---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 09:18:47 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1794492721 50
1794492726 50
1794492731 50
1794492736 50
1794492741 50
1794492746 51
1794492751 51
1794492756 51
1794492761 51
1794492766 51
1794492771 51
1794492776 51
1794492781 51
1794492786 51
1794492791 51
1794492796 51
1794492801 51
1794492806 51
1794492811 51
1794492816 51
```
</details>

---

