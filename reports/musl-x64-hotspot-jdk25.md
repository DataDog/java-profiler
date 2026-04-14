---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-14 14:58:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (7 unique values: 55-78 cores)</summary>

```
1776192776 61
1776192781 61
1776192786 61
1776192791 63
1776192796 63
1776192801 63
1776192806 63
1776192811 63
1776192816 63
1776192821 59
1776192826 59
1776192831 59
1776192836 59
1776192841 59
1776192846 55
1776192851 55
1776192856 60
1776192861 60
1776192866 60
1776192871 60
```
</details>

---

